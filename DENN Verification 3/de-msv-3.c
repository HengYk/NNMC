#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <string.h>
// #include <assert.h>
#include <stdbool.h>
#include <math.h>

#define ACTIVATION_FUNC(x)              (1/(1+exp(-(x))))

#define ORIGINAL_OPTIMIZED_PARAM     "E:/bpnn/dataset/original_optimized_param.txt"
#define IN_PATH                     "E:/bpnn/dataset/in_reduced.txt"
#define OUT_PATH                    "E:/bpnn/dataset/out_reduced.txt"

#define nVar 26

#define IN_N                            3
#define OUT_N                           1
#define HIDDEN_N                        5
#define OFFSET                          0

#define D   IN_N
#define Q   HIDDEN_N
#define L   OUT_N

#define D   IN_N
#define Q   HIDDEN_N
#define L   OUT_N
#define U1  LEARN_RATE1
#define U2  LEARN_RATE2

#define SEEK_SET   0
#define RAND_MAX   32767

typedef int size_t;

typedef int bool;
#define true 1
#define false 0

/** 结构参数 */
double v[D][Q];
double w[Q][L];
double r[Q];
double o[L];

/** 中间结果 */
double x[D];
double b[Q];
double y[L];
double yc[L];

/** 评价参数 */
double Ek;

struct _iobuf {
	char *_ptr;
	int   _cnt;
	char *_base;
	int   _flag;
	int   _file;
	int   _charbuf;
	int   _bufsiz;
	char *_tmpfname;
	};
typedef struct _iobuf FILE;

FILE *in_file_3; // ORIGINAL_OPTIONAL_PARAM
FILE *in_file_1; // IN_PATH
FILE *in_file_2; // OUT_PATH

typedef struct
{
	double position[nVar];
	double fitness;

} individual;

individual originalInd;
individual optionalInd;

/** 读取神经网络结构参数 */
bool read_param(double *in, FILE *in_file)
{
    // assert(in);

    #define BUFFER_SIZE 256
    char buffer[BUFFER_SIZE];

    if (in_file)
    {
        int index = 0;
        while (fgets(buffer, BUFFER_SIZE, in_file) != NULL)
        {
            if (index >= OFFSET) {
                char *token = strtok(buffer, "\0");
                in[index - OFFSET] = strtod(token, NULL);
            }
            index ++;

            if (index == nVar) {
                break;
            }
        }
        return true;
    }
    return false;
}

/** 读取神经网络输入样本 */
bool read_sample(double *in, double *out)
{
    // assert(in && out);

    #define BUFFER_SIZE 256
    char buffer[BUFFER_SIZE];

    if (in_file_1 && in_file_2)
    {
        if (fgets(buffer, BUFFER_SIZE, in_file_1) != NULL)
        {
            char *token = strtok(buffer, ",");

            for (size_t i = 0; i < IN_N; i++)
            {
                if (token == NULL)
                {
                    fprintf(stderr, "the format of input is not correct!\n");
                    return false;
                }
                in[i] = strtod(token, NULL);
                token = strtok(NULL, ",");
            }
        }
        else
        {
            return false;
        }

        if (fgets(buffer, BUFFER_SIZE, in_file_2) != NULL)
        {
            out[0] = strtod(buffer, NULL);
        }
        else
        {
            return false;
        }
        return true;
    }

    return false;
}

/** 评价网络11 */
double score_func() {

    for (int h = 0; h < Q; h++) {
        double alpha_h = 0;
        for (int i = 0; i < D; i++)
            alpha_h += v[i][h] * x[i];
        b[h] = ACTIVATION_FUNC(alpha_h - r[h]);
    }

    Ek = 0;

    for (int j = 0; j < L; j++) {
        double beta_j = 0;
        for (int h = 0; h < Q; h++)
            beta_j += w[h][j] * b[h];
        yc[j] = ACTIVATION_FUNC(beta_j - o[j]);
        Ek += (yc[j] - y[j]) * (yc[j] - y[j]);
    }

    // printf("%f\n", Ek);
    return 0.5 * Ek;
}

/** 网络性能评估 */
double eval_bpnn() {

    double precent = 0.0;
    int count = 0;
    int co = 0;

    while (read_sample(x, y)) {
        count ++;
        double temp = score_func();

        if (temp < 0.000001) {
            co ++;
        }
    }

    precent = co / (double)count;

    fseek(in_file_1, 0, SEEK_SET);
    fseek(in_file_2, 0, SEEK_SET);

    return precent;
}

/** 赋值结构参数 */
void assign_v_r_w_o(double *val) {

    int index = 0;

    for (int i = 0; i < D; i ++) {
        for (int j = 0; j < Q; j ++) {
            v[i][j] = *(val + index);
            index ++;
        }
    }

    for (int i = 0; i < Q; i ++) {
        for (int j = 0; j < L; j ++) {
            w[i][j] = *(val + index);
            index ++;
        }
    }

    for (int i = 0; i < Q; i ++) {
        r[i] = *(val + index);
        index ++;
    }

    for (int i = 0; i < L; i ++) {
        o[i] = *(val + index);
        index ++;
    }
}

int main()
{
    in_file_1 = fopen(IN_PATH, "r");
    in_file_2 = fopen(OUT_PATH, "r");
    in_file_3 = fopen(ORIGINAL_OPTIMIZED_PARAM, "r");

    // 拿原始数据和进化数据比较
    // 原始数据
    if (!read_param(originalInd.position, in_file_3)) {
        fprintf(stderr, "Individual originalInd init fail");
    }

    assign_v_r_w_o(originalInd.position);
    double original_res = eval_bpnn();

    // 进化数据
    if (!read_param(optionalInd.position, in_file_3)) {
        fprintf(stderr, "Individual optionalInd init fail");
    }

    assign_v_r_w_o(optionalInd.position);
    double optional_1000_res = eval_bpnn();

    bool flag = false;
    if (optional_1000_res >= original_res) {
        flag = true;
    }

    /* 对新模型优化结果的验证（强化模型的正确性）

    define p: original_res > 0.9
    define q: optional_1000_res > 0.9
    define r: original_res < oprional_1000_res
    som ((p and q) -> r)

    结论：一定范围内随机浮动生成的种群，种群优化的最终结果优于原始结果。
                但是在已知网络结构充分随机生成的种群，种群优化的结果不一定优于原始种群。
    */

    printf("flag:%d   original:%f   optional_1000_res:%f\n", flag, original_res, optional_1000_res);

    fclose(in_file_1);
    fclose(in_file_2);
    fclose(in_file_3);

    return 0;
}
