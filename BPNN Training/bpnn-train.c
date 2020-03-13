#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define IN_N                            3
#define OUT_N                           1
#define HIDDEN_N                        5
#define LOOP_N                          5000
#define E_MIN                           0.000001
#define LEARN_RATE1                     0.3
#define LEARN_RATE2                     0.4

#define ACTIVATION_FUNC(x)              (1/(1+exp(-(x))))

#define TEST_IN_PATH                    "../bpnn/dataset/test_in.txt"
#define TEST_OUT_PATH                   "../bpnn/dataset/test_out.txt"
#define SAVE_PARAM_PATH                 "../bpnn/dataset/bpnn_param.txt"

#define RAND                    (rand() / (double)(RAND_MAX))

#define D   IN_N
#define Q   HIDDEN_N
#define L   OUT_N
#define U1  LEARN_RATE1
#define U2  LEARN_RATE2

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

double Ek;

FILE *in_file = NULL;
FILE *out_file = NULL;

/**
    文件数据读入操作
*/
bool read_data(double *in, double *out)
{
    #define BUFFER_SIZE 256
    char buffer[BUFFER_SIZE];

    if (in_file && out_file)
    {
        if (fgets(buffer, BUFFER_SIZE, in_file) != NULL)
        {
            char *token = strtok(buffer, ",");

            for (size_t i = 0; i < IN_N; i++)
            {
                if (token == NULL)
                {
                    fprintf(stderr, "The format of input is not correct!\n");
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

        if (fgets(buffer, BUFFER_SIZE, out_file) != NULL)
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

/**
    重置文件数据游标到文件的开头
*/
bool reset_cursor(void)
{
    fseek(in_file, 0, SEEK_SET);
    fseek(out_file, 0, SEEK_SET);
    return true;
}

/**
    神经网络训练过程1（一次前向+一次反向）
*/
bool train_once() {

    if (!read_data(x, y))
        return false;

    /* IN_N --> HIDDEN_N */
    for (size_t h = 0; h < Q; h++) {
        double alpha_h = 0;
        for (size_t i = 0; i < D; i++)
            alpha_h += v[i][h] * x[i];
        b[h] = ACTIVATION_FUNC(alpha_h - r[h]);
    }

    /* HIDDEN_N --> OUT_N */
    for (size_t j = 0; j < L; j++) {
        double beta_j = 0;
        for (size_t h = 0; h < Q; h++)
            beta_j += w[h][j] * b[h];
        yc[j] = ACTIVATION_FUNC(beta_j - o[j]);
    }

    Ek = 0;

    /* Grad and Cost */
    for (size_t j = 0; j < L; j++) {
        g[j] = yc[j] * (1 - yc[j]) * (y[j] - yc[j]);
        Ek += (yc[j] - y[j]) * (yc[j] - y[j]);
    }

    Ek = 0.5 * Ek;

    /* OUT_N --> HIDDEN_N */
    for (size_t h = 0; h < Q; h++) {
        double temp = 0;
        for (size_t j = 0; j < L; j++)
            temp += w[h][j] * g[j];
        e[h] = b[h] * (1 - b[h]) * temp;
    }

    /* Update param */
    for (size_t i = 0; i < D; i++)
        for (size_t h = 0; h < Q; h++)
            v[i][h] += U2 * e[h] * x[i];
    for (size_t h = 0; h < Q; h++)
        for (size_t j = 0; j < L; j++)
            w[h][j] += U1 * g[j] * b[h];
    for (size_t h = 0; h < Q; h++)
        r[h] += ((-U2) * e[h]);
    for (size_t j = 0; j < L; j++)
        o[j] += ((-U1) * g[j]);

    return true;
}

/**
    保存神经网路结构参数
*/
 bool save_parameter() {

    FILE *out = NULL;
    out = fopen(SAVE_PARAM_PATH, "w+");

    if (out == NULL) {
        fprintf(stderr, "Cannot open %s.\n", SAVE_PARAM_PATH);
        return false;
    }

    for (size_t i = 0; i < D; i++)
        for (size_t h = 0; h < Q; h++)
            fprintf(out, "%f\n", v[i][h]);
    for (size_t h = 0; h < Q; h++)
        for (size_t j = 0; j < L; j++)
            fprintf(out, "%f\n", w[h][j]);
    for (size_t h = 0; h < Q; h++)
        fprintf(out, "%f\n", r[h]);
    for (size_t j = 0; j < L; j++)
        fprintf(out, "%f\n", o[j]);

    fclose(out);

    return true;
}

/**
    神经网络结构的初始化
*/
void bpnn_init(void) {
    srand((unsigned) time(NULL));
    for (size_t i = 0; i < D; i++)
        for (size_t h = 0; h < Q; h++)
            v[i][h] = RAND;
    for (size_t h = 0; h < Q; h++)
        for (size_t j = 0; j < L; j++)
            w[h][j] = RAND;
    for (size_t h = 0; h < Q; h++)
        r[h] = RAND;
    for (size_t j = 0; j < L; j++)
        o[j] = RAND;
}

/**
    神经网络训练过程2（多次前向+多次反向）
*/
void bpnn_train() {

    reset_cursor();

    int train_c = 0;
    double E = 0;
    while (train_c < LOOP_N) {
        size_t count = 0;
        while (train_once()) {
            count++;
            E += Ek;
        }

        E /= count;

        train_c++;
        printf("Iter: %d   Cost: %0.8f\n", train_c, E);
        reset_cursor();
        if (E < E_MIN)
            break;
    }

    if (save_parameter())
        printf("Saved successfully in %s\n", SAVE_PARAM_PATH);
    else
        printf("I am sorry.\n");
}

int main(void)
{
    in_file = fopen(TEST_IN_PATH, "r");
    if (in_file == NULL)
    {
        fprintf(stderr, "Cannot open %s.\n", TEST_IN_PATH);
        return 0;
    }

    out_file = fopen(TEST_OUT_PATH, "r");
    if (out_file == NULL)
    {
        fprintf(stderr, "Cannot open %s.\n", TEST_OUT_PATH);
        return 0;
    }

    bpnn_init();
    bpnn_train();

    fclose(in_file);
    fclose(out_file);

    return 0;
}
