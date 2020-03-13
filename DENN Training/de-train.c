#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#define nVar 26
#define nPop 20
#define Iter 1000
#define F 0.5
#define CR 0.8

#define BPNN_PARAM_PATH             "E:/bpnn/dataset/bpnn_param.txt"
#define MODIFIED_PARAM_PATH         "E:/bpnn/dataset/modified_param.txt"
#define IN_PATH                     "E:/bpnn/dataset/in.txt"
#define OUT_PATH                    "E:/bpnn/dataset/out.txt"
#define ITERATIVE_PARAM             "E:/bpnn/dataset/iterative_param.txt"

#define CONST                           26
#define OFFSET                          0

#define IN_N                            3
#define OUT_N                           1
#define HIDDEN_N                        5

#define D   IN_N
#define Q   HIDDEN_N
#define L   OUT_N

#define ACTIVATION_FUNC(x)              (1/(1+exp(-(x))))

typedef struct
{
	double position[nVar];
	double fitness;

} individual;

typedef struct
{
	individual inArray[nPop];

} population;

static population initPop;
static population mutationPop;
static population crossoverPop;

static FILE *in_file; // BPNN_PARAM_PATH
static FILE *in_file_1; // IN_PATH
static FILE *in_file_2; // OUT_PATH
static FILE *out_file; // ITERATIVE_PARAM

/** 结构参数 */
static double v[D][Q];
static double w[Q][L];
static double r[Q];
static double o[L];

/** 中间结果 */
static double x[D];
static double b[Q];
static double y[L];
static double yc[L];

/** 评价参数 */
static double Ek;

/** 读取神经网络结构参数 */
bool read_param(double *in, FILE *in_file)
{
    assert(in);

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
    assert(in && out);

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

    return 0.5 * Ek;
}

/** 评价网络12 */
double cal_fitness() {

    double fitness = 0.0;

    while (read_sample(x, y)) {
        double temp = score_func();
        fitness += temp;
    }

    fseek(in_file_1, 0, SEEK_SET);
    fseek(in_file_2, 0, SEEK_SET);

    return fitness;
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

/** 种群初始化 */
void init() {

    for (int i = 0; i < nPop; i ++) {
        if (!read_param(initPop.inArray[i].position, in_file)) {
            fprintf(stderr, "Individual %d init fail", i);
        }
    }

    for (int i = 0; i < nPop; i ++) {
        assign_v_r_w_o(initPop.inArray[i].position);
        initPop.inArray[i].fitness = cal_fitness();
    }
}

/** 种群变异 */
void mutation() {

    for (int i = 0; i < nPop; i ++) {
        int r1 = 0, r2 = 0, r3 = 0;
        while (r1 == i || r2 == i || r3 == i || r1 == r2 || r2 == r3 || r1 == r3) {
            r1 = (int) rand() % nPop;
            r2 = (int) rand() % nPop;
            r3 = (int) rand() % nPop;
        }

        for (int j = 0; j < nVar; j ++) {
            mutationPop.inArray[i].position[j] = initPop.inArray[r1].position[j]
                 + F * (initPop.inArray[r2].position[j] - initPop.inArray[r3].position[j]);
        }
    }
}

/** 种群交叉 */
void crossover() {

    for (int i = 0; i < nPop; i ++) {
        for (int j = 0; j < nVar; j ++) {
            double rand_cr = (double) rand() / RAND_MAX;

            if (rand_cr < CR) {
                crossoverPop.inArray[i].position[j] = mutationPop.inArray[i].position[j];
            } else {
                crossoverPop.inArray[i].position[j] = initPop.inArray[i].position[j];
            }
        }
    }
}

/** 种群选择 */
void selection() {

    for (int i = 0; i < nPop; i ++) {
        assign_v_r_w_o(crossoverPop.inArray[i].position);
        crossoverPop.inArray[i].fitness = cal_fitness();
        if (crossoverPop.inArray[i].fitness < initPop.inArray[i].fitness) {
            for (int j = 0; j < nVar; j ++) {
                initPop.inArray[i].position[j] = crossoverPop.inArray[i].position[j];
            }
            initPop.inArray[i].fitness = crossoverPop.inArray[i].fitness;
        }
    }

}

/** 打印每一代的全局最优 */
void print(int iter) {

    int minIndex = 0;
    for (int i = 0; i < nPop; i ++) {
        if (initPop.inArray[i].fitness < initPop.inArray[minIndex].fitness) {
            minIndex = i;
        }
    }

    printf("iter:%d   fitness:%0.6f   ", iter, initPop.inArray[minIndex].fitness);
    printf("[");
    for (int j = 0; j < nVar; j ++) {
        printf("%0.6f ", initPop.inArray[minIndex].position[j]);
        fprintf(out_file, "%0.6f ", initPop.inArray[minIndex].position[j]);

    }
    printf("]\n");
    fprintf(out_file, "%0.6f", initPop.inArray[minIndex].fitness);
    fprintf(out_file, "\n");
}

int main(void)
{
    printf("the program is running!\n");

    in_file = fopen(MODIFIED_PARAM_PATH, "r");
    in_file_1 = fopen(IN_PATH, "r");
    in_file_2 = fopen(OUT_PATH, "r");
    out_file = fopen(ITERATIVE_PARAM, "a");

    init();
    srand(time(NULL));

    int iter = 0;
    while (iter ++ < Iter) {
        mutation();
        crossover();
        selection();
        print(iter);
    }

    fclose(in_file);
    fclose(in_file_1);
    fclose(in_file_2);
    fclose(out_file);

	return 0;
}
