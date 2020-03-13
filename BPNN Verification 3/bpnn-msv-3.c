#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define IN_N                            3           /* INPUT NODE */
#define OUT_N                           1           /* OUTPUT_NODE */
#define HIDDEN_N                        5          /* HIDDEN_NODE */
#define LEARN_RATE1                     0.3
#define LEARN_RATE2                     0.4
#define Ee                              0.00000100 /* Modified by Yk */

#define ACTIVATION_FUNC(x)              (1/(1+exp(-(x))))

#define SAVE_PARAM_PATH                 "../bpnn/dataset/bpnn_param.txt"
// #define SAVE_RESULT_PATH                "../bpnn/dataset/bpnn_result.txt"

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

double v[D][Q];
double w[Q][L];
double r[Q];
double o[L];

double g[L];
double e[Q];
double f[D]; // Modified by Yk

double x[D];
double b[Q];
double y[L];
double yc[L];

double Ek; // From help-pro-bak-2-msv-2
double aveEk; // From help-pro-bak-2-msv

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

/**
    读入神经网络结构参数
*/
bool read_parameter() {

    FILE* in = NULL;
    in = fopen(SAVE_PARAM_PATH, "r");

    if (in == NULL) {
        fprintf(stderr, "Cannot open %s\n", SAVE_PARAM_PATH);
        return false;
    }

    char buffer[256];

    for (size_t i = 0; i < D; i++) {
        for (size_t h = 0; h < Q; h++) {
            fscanf(in, "%s", buffer);
            v[i][h] = strtod(buffer, NULL);
        }
    }

    for (size_t h = 0; h < Q; h++) {
        for (size_t j = 0; j < L; j++) {
            fscanf(in, "%s", buffer);
            w[h][j] = strtod(buffer, NULL);
        }
    }

    for (size_t h = 0; h < Q; h++) {
        fscanf(in, "%s", buffer);
        r[h] = strtod(buffer, NULL);
    }

    for (size_t j = 0; j < L; j++) {
        fscanf(in, "%s", buffer);
        o[j] = strtod(buffer, NULL);
    }

    fclose(in);

    return true;
}

/**
    如何对异常样本进行有针对性的修复？
*/
void bpnn_sim_single() {

    /*
    FILE *out = NULL;
    out = fopen(SAVE_RESULT_PATH, "w+");

    if (out == NULL) {
        fprintf(stderr, "Cannot open %s.\n", SAVE_RESULT_PATH);
        return;
    } */

    /* 定义输入层 */
    double ax[3] = { 0.991998, 0.919734, 0.859287 };
    double by[1] = { 0.923673 }; // 真实值
    double by_ = 0; // 虚假的真实值，即可以绕过模型的值
    double Ek_ = 0; // 表示所谓“明显的误差”

    int iter = 0;

    Ek = 0.00007368;
    aveEk = 0.00000215;
    
    while (Ek > aveEk) {

        /* 计算隐藏层的输出结果 */
        for (size_t h = 0; h < Q; h++) {
            double alpha_h = 0;
            for (size_t i = 0; i < D; i++)
                alpha_h += v[i][h] * ax[i];
            b[h] = ACTIVATION_FUNC(alpha_h - r[h]);
        }

        /* 计算输出层的输出结果 */
        for (size_t j = 0; j < L; j++) {
            double beta_j = 0;
            for (size_t h = 0; h < Q; h++)
                beta_j += w[h][j] * b[h];
            yc[j] = ACTIVATION_FUNC(beta_j - o[j]);
        }

        Ek = 0;

        /* 计算损失值*/
        for (size_t j = 0; j < L; j++) {
           Ek += (yc[j] - by[j]) * (yc[j] - by[j]);
        }
        Ek = 0.5 * Ek;

        /* 反向求解输出层的导数 */
        for (size_t j = 0; j < L; j++) {
            g[j] = yc[j] * (1 - yc[j]) * (by[j] - yc[j]);
        }

        /* 反向求解隐藏层的导数 */
        for (size_t h = 0; h < Q; h++) {
            double temp = 0;
            for (size_t j = 0; j < L; j++)
                temp += w[h][j] * g[j];
            e[h] = b[h] * (1 - b[h]) * temp;
        }

        /* 反向求解输入层的导数 */
        for (size_t i = 0; i < D; i++) {
            double temp1 = 0;
            for (size_t h = 0; h < Q; h++) {
                temp1 += v[i][h] * e[h];
            }
            f[i] = temp1;
        }

        /* 引入符号函数，调整输入层*/
        // 有针对性地调整输入层
        for (size_t i = 0; i < D; i++) {
            if (f[i] >= 0) ax[i] += Ee;
            if (f[i] < 0) ax[i] -= Ee;
        }

        iter += 1;

        /* 将打印结果输出到文件中 */
        // fprintf(out, "\nf[0]=%f  f[1]=%f  f[2]=%f  Ek=%f  by=%f[yc=%f]\n", f[0], f[1], f[2], Ek, by[0], yc[0]);
        // fprintf(out, "\nx[0]=%f  x[1]=%f  x[2]=%f by iter=%d\n", ax[0], ax[1], ax[2], iter);
    }

    by_ = ( ax[0] + ax[1] + ax[2] ) / 3;
    Ek_ = (by_ - by[0]) * (by_ - by[0]);

    // 与初始输出值对比，如果预测结果的误差小于平均误差，而实际结果的误差远大于平均误差
    // 则认为我们使用一个明显错误的样本通过了模型的检测，此处我们可以视为“模型的健壮性”验证
    // 说明模型本身是有待进一步强化的。
    bool check_attack = false;
    if (Ek < aveEk && Ek_ >= aveEk) {
        check_attack = true;
    }

    printf("check_attack: %d", check_attack);

    // fclose(out);

    /*模型的健壮性验证

    define p : Ek < aveEk;
    define q : Ek_ >= aveEk;
    som (p and q)

    模型的健壮性验证*/

    // 特别说明：此处还有待扩展，即采用大量反例样本进行验证而不单单是一个，大量样本论证之后的模型才更具有说服力。
}

int main()
{
    if (!read_parameter())
    {
        printf("Read param is failed in %s!\n", SAVE_PARAM_PATH);
        return 0;
    }

    // 第三步，将不满足要求的样本有针对性地更正到满足要求
    bpnn_sim_single();

    return 0;
}

