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
#define LEARN_RATE1                     0.3
#define LEARN_RATE2                     0.4

#define ACTIVATION_FUNC(x)              (1/(1+exp(-(x))))

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
double aveEk = 0.00000215; // From help-pro-bak-2-msv

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

    fclose(in);

    return true;
}

/**
    �����Ч�ؼ���쳣���������¶����쳣����׼��
*/
void bpnn_check_single() {

    /* ��������� */
    // failure
    double ax[3] = { 0.991998, 0.919734, 0.859287 };
    double by[1] = { 0.923673 };

    // success
    // double ax[3] = { 0.712532, 0.451378, 0.920685 };
    // double by[1] = { 0.694865 };

    /* �������ز�������� */
    for (size_t h = 0; h < Q; h++) {
        double alpha_h = 0;
        for (size_t i = 0; i < D; i++)
            alpha_h += v[i][h] * ax[i];
        b[h] = ACTIVATION_FUNC(alpha_h - r[h]);
    }

    /* ���������������� */
    for (size_t j = 0; j < L; j++) {
        double beta_j = 0;
        for (size_t h = 0; h < Q; h++)
            beta_j += w[h][j] * b[h];
        yc[j] = ACTIVATION_FUNC(beta_j - o[j]);
    }

    Ek = 0;

    /* ������ʧֵ*/
    for (size_t j = 0; j < L; j++) {
       Ek += (yc[j] - by[j]) * (yc[j] - by[j]);
    }
    Ek = 0.5 * Ek;

    // ����������Ԥ������ʵ����������������Ԥ������ƽ�������жԱ�
    // ���ǰ��С�ں��ߣ�����Ϊ����Ϊ�ɿ��������˴�����Ϊ����������ȷ����֤����
    int check_flag = false; // ���Ϊʧ��
    if (Ek <= aveEk) {
        check_flag = true; // ���Ϊ�ɹ�
    }

    if (check_flag) {
        printf("Ek <= aveEk : %0.8f <= %0.8f --> #success#", Ek, aveEk);
    } else {
        printf("Ek > aveEk : %0.8f > %0.8f  -->  #failure#", Ek, aveEk);
    }

    /* ��������������ȷ����֤

    define p0 : Ek != 0;
    define p1 : aveEk != 0;
    define q : Ek < aveEk;
    som (p0 and p1 and q)

    ��������������ȷ����֤*/
}

int main()
{
    if (!read_parameter())
    {
        printf("Read param is failed in %s!\n", SAVE_PARAM_PATH);
        return 0;
    }

    // �ڶ��������ƶ���׼֮���ж���������Ƿ�����Ҫ��
    bpnn_check_single();

    return 0;
}
