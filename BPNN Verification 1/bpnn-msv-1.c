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
#define E_MIN                           0.000001
#define LEARN_RATE1                     0.3
#define LEARN_RATE2                     0.4

#define ACTIVATION_FUNC(x)              (1/(1+exp(-(x))))

#define IN_PATH                         "../bpnn/dataset/in_reduced.txt"
#define OUT_PATH                        "../bpnn/dataset/out_reduced.txt"
#define SAVE_PARAM_PATH                 "../bpnn/dataset/bpnn_param.txt"

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

double Ek;
double maxEk; // Modified by Yk
double minEk; // Modified by Yk
double aveEk; // Modified by Yk

double percent;

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

FILE *in_file = NULL;
FILE *out_file = NULL;

/**
    �ļ����ݶ������
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
    ����������ṹ����
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

    /* ���Դ��뱣��
    fscanf(in, "%s", buffer);
    // printf("%s\n", buffer); // D=3
    char * token = strtok(buffer, "=");
    // printf("%s\n", token); // D
    token = strtok(NULL, "\0");
    // printf("%s\n", token); // 3
    int x = strtod(token, NULL);
    // printf("%d", x);
    */

    fclose(in);

    return true;
}

/**
    ������ǵĶ����������ж����������Դﵽ���ǵ�ѵ��Ҫ��
*/
void bpnn_sim() {

    maxEk = 0, minEk = 1, aveEk = 0;
    int count = 0; // �ܵ�������
    int co = 0; // ����������������
    percent = 0.0;
    while (read_data(x, y)) {
        count++;

        /* Compute b[h] */
        for (size_t h = 0; h < Q; h++) {
            double alpha_h = 0;
            for (size_t i = 0; i < D; i++)
                alpha_h += v[i][h] * x[i];
            b[h] = ACTIVATION_FUNC(alpha_h - r[h]);
        }

        Ek = 0;

        /* Compute yc[j] */
        for (size_t j = 0; j < L; j++) {
            double beta_j = 0;
            for (size_t h = 0; h < Q; h++)
                beta_j += w[h][j] * b[h];
            yc[j] = ACTIVATION_FUNC(beta_j - o[j]);
            Ek += (yc[j] - y[j]) * (yc[j] - y[j]);
        }

        Ek = 0.5 * Ek;

        // ���ģ������Ľ������ں���ķ�Χ�ڣ�������Ϊ������Ԥ�����ǿ��Խ��ܵ�
        // �˴����ǿ������Ϊģ�͵ġ���ȷ�ԡ���֤
        if (Ek < E_MIN) {
            co ++;
        }

        printf("Index: %d   Cost: %0.8f ==> ", count, Ek);
        printf("Input: ");
        for (size_t i = 0; i < D; i++)
            printf("%f ", x[i]);
        printf("Output:");
        for (size_t j = 0; j < L; j++)
            printf("%f[%f] ", y[j], yc[j]);
        printf("\n");

        maxEk = (Ek > maxEk) ? Ek : maxEk;
        minEk = (Ek < minEk) ? Ek : minEk;
        aveEk += Ek;
    }

    aveEk = aveEk / count;
    percent = co / (double) count;

    printf("MaxCost: %0.8f  MinCost: %0.8f  AveCost: %0.8f\n", maxEk, minEk, aveEk);
    printf("Percent: %f\n", percent * 100);

    // ����������ʵ������������ͳ�Ƶõ���
    bool check_model = false; // ģ���޷���ȷ���90%���ϵ�����
    if (percent > 0.9) {
        check_model = true; // ģ�Ϳ�����ȷ���90%���ϵ�����
    }

    printf("%d\n", check_model);

    /* ģ�͵���ȷ����֤

    define p: precent > 0.9
    define q: check_model = 1
    ? som (p and next q)
    ? som (p and som  q)
    ? fin (p or q)

    ����

    define p: precent > 0.9
    fin p

    ģ�͵���ȷ����֤*/
}

int main()
{
    if (!read_parameter())
    {
        printf("Read param is failed in %s!\n", SAVE_PARAM_PATH);
        return 0;
    }

    in_file = fopen(IN_PATH, "r");
    if (in_file == NULL)
    {
        fprintf(stderr, "Cannot open %s.\n", IN_PATH);
        return 0;
    }

    out_file = fopen(OUT_PATH, "r");
    if (out_file == NULL)
    {
        fprintf(stderr, "Cannot open %s.\n", OUT_PATH);
        return 0;
    }

    // ��һ��������˵��ѡ�ö��������ƶ���׼�ĺ�����
    bpnn_sim();

    fclose(in_file);
    fclose(out_file);

    return 0;
}
