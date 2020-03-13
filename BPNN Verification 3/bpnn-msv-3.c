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
    ��ζ��쳣��������������Ե��޸���
*/
void bpnn_sim_single() {

    /*
    FILE *out = NULL;
    out = fopen(SAVE_RESULT_PATH, "w+");

    if (out == NULL) {
        fprintf(stderr, "Cannot open %s.\n", SAVE_RESULT_PATH);
        return;
    } */

    /* ��������� */
    double ax[3] = { 0.991998, 0.919734, 0.859287 };
    double by[1] = { 0.923673 }; // ��ʵֵ
    double by_ = 0; // ��ٵ���ʵֵ���������ƹ�ģ�͵�ֵ
    double Ek_ = 0; // ��ʾ��ν�����Ե���

    int iter = 0;

    Ek = 0.00007368;
    aveEk = 0.00000215;
    
    while (Ek > aveEk) {

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

        /* ������������ĵ��� */
        for (size_t j = 0; j < L; j++) {
            g[j] = yc[j] * (1 - yc[j]) * (by[j] - yc[j]);
        }

        /* ����������ز�ĵ��� */
        for (size_t h = 0; h < Q; h++) {
            double temp = 0;
            for (size_t j = 0; j < L; j++)
                temp += w[h][j] * g[j];
            e[h] = b[h] * (1 - b[h]) * temp;
        }

        /* ������������ĵ��� */
        for (size_t i = 0; i < D; i++) {
            double temp1 = 0;
            for (size_t h = 0; h < Q; h++) {
                temp1 += v[i][h] * e[h];
            }
            f[i] = temp1;
        }

        /* ������ź��������������*/
        // ������Եص��������
        for (size_t i = 0; i < D; i++) {
            if (f[i] >= 0) ax[i] += Ee;
            if (f[i] < 0) ax[i] -= Ee;
        }

        iter += 1;

        /* ����ӡ���������ļ��� */
        // fprintf(out, "\nf[0]=%f  f[1]=%f  f[2]=%f  Ek=%f  by=%f[yc=%f]\n", f[0], f[1], f[2], Ek, by[0], yc[0]);
        // fprintf(out, "\nx[0]=%f  x[1]=%f  x[2]=%f by iter=%d\n", ax[0], ax[1], ax[2], iter);
    }

    by_ = ( ax[0] + ax[1] + ax[2] ) / 3;
    Ek_ = (by_ - by[0]) * (by_ - by[0]);

    // ���ʼ���ֵ�Աȣ����Ԥ���������С��ƽ������ʵ�ʽ�������Զ����ƽ�����
    // ����Ϊ����ʹ��һ�����Դ��������ͨ����ģ�͵ļ�⣬�˴����ǿ�����Ϊ��ģ�͵Ľ�׳�ԡ���֤
    // ˵��ģ�ͱ������д���һ��ǿ���ġ�
    bool check_attack = false;
    if (Ek < aveEk && Ek_ >= aveEk) {
        check_attack = true;
    }

    printf("check_attack: %d", check_attack);

    // fclose(out);

    /*ģ�͵Ľ�׳����֤

    define p : Ek < aveEk;
    define q : Ek_ >= aveEk;
    som (p and q)

    ģ�͵Ľ�׳����֤*/

    // �ر�˵�����˴����д���չ�������ô�����������������֤����������һ��������������֤֮���ģ�ͲŸ�����˵������
}

int main()
{
    if (!read_parameter())
    {
        printf("Read param is failed in %s!\n", SAVE_PARAM_PATH);
        return 0;
    }

    // ����������������Ҫ�������������Եظ���������Ҫ��
    bpnn_sim_single();

    return 0;
}

