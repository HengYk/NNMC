#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#define ITERATIVE_PARAM_PATH        "../bpnn/dataset/iterative_param.txt"

#define D   IN_N
#define Q   HIDDEN_N
#define L   OUT_N
#define U1  LEARN_RATE1
#define U2  LEARN_RATE2

#define SEEK_SET   0
#define RAND_MAX   32767

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

FILE *in_file;  // ITERATIVE_PARAM

int main(void)
{
    printf("the program is running!\n");

    in_file = fopen(ITERATIVE_PARAM_PATH, "r");

    double *res = (double *)malloc(sizeof(double) * 10);

    if (!in_file) {
        fprintf(stderr, "Cannot open %s!", in_file);
    }

    char buffer[256];
    int index = 0;

    while (fgets(buffer, 256, in_file) != NULL) {
        char *token = strtok(buffer, " ");
        for (int i = 0; i < 27; i ++) {
            if (i == 25) {
                res[index] = strtod(token, NULL);
                token = strtok(NULL, " ");
            }
            strtod(token, NULL);
            token = strtok(NULL, " ");
        }
        index ++;
        if (index == 10) {
            break;
        }
    }

    for (int i = 0; i < 10; i ++) {
        printf("%f\n", res[i]);
    }

    /* 对网络结构优化过程的验证

    define p: res[0] >= res[1];
    define q: res[1] >= res[2];
    alw (p and q)

    结论：在网络结构的优化过程中，种群中的网络结构总是变得越来越好。
    */
    fclose(in_file);

	return 0;
}
