#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define ACTIVATION_FUNC(x)              (1/(1+exp(-(x))))

#define IN_PATH                         "../bpnn/dataset/in.txt"
#define OUT_PATH                        "../bpnn/dataset/out.txt"
#define MODIFIED_PARAM_PATH             "../bpnn/dataset/modified_param_000100.txt"

#define nPop                            3
#define nVar                            26

#define IN_N                            3
#define OUT_N                           1
#define HIDDEN_N                        5
#define OFFSET                          0

#define D   IN_N
#define Q   HIDDEN_N
#define L   OUT_N

#define SEEK_SET   0
#define RAND_MAX   32767

typedef int size_t;

typedef int bool;

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

FILE *in_file_1;  // IN_PATH
FILE *in_file_2;  // OUT_PATH
FILE *in_file_3;  // MODIFIED_PARAM_PATH  huo  MODIFIED_PARAM_PATH_1

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

typedef struct
{
	double position[nVar];
	double fitness;

} individual;

individual randInd;

/** 读取神经网络结构参数 */
bool read_param(double *in, FILE *in_file)
{

    #define BUFFER_SIZE 256
    char buffer[BUFFER_SIZE];

    if (in_file)
    {
        int index = 0;
        char * temp;
        while ((temp = fgets(buffer, BUFFER_SIZE, in_file)) != NULL)
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

        if (temp == NULL) {
            return false;
        }

        return true;
    }

    return false;
}

/** 读取神经网络输入样本 */
bool read_sample(double *in, double *out)
{
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
    in_file_3 = fopen(MODIFIED_PARAM_PATH, "r");

    double percent_old = 0.914600;
    double* percents;
    percents = (double *)malloc(sizeof(double) * nPop);
    int index = 0;

    while (read_param(randInd.position, in_file_3)) {
        assign_v_r_w_o(randInd.position);

        /*
        for (int i = 0; i < nVar; i ++) {
            printf("%f\n", randInd.position[i]);
        }
        printf("\n");*/

        percents[index] = eval_bpnn();
        index ++;
    }

    double percent_rand = percent_old;
    for (int i = 0; i < nPop; i ++) {
        printf("percent: %f\n", percents[i]);
        if (percents[i] < percent_rand) {
            percent_rand = percents[i];
        }
    }
    printf("\n");
    printf("percent_old: %f\n", percent_old);
    printf("percent_rand: %f\n", percent_rand);

    fclose(in_file_1);
    fclose(in_file_2);
    fclose(in_file_3);

    return 0;
}
/**
percent: 0.914300
percent: 0.912900
percent: 0.914800

percent_old: 0.914600
percent_rand: 0.912900

Process returned 0 (0x0)   execution time : 0.406 s
Press any key to continue.

---------------------
模型的随机性验证
此性质务必查看modified_param_000100.txt，性质必定从中产生。

define q: percent_rand < percent_old
som q

结论：随机产生的网络结构可能弱于原始网络，网络结构的随机性可能会破坏模型。
**/
