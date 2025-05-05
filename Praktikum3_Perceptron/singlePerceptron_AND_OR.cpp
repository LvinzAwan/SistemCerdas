#include <iostream>
#include <stdio.h>
#include <stdlib.h>

double d_rand() {
    return (((double)(rand() % 32767) / 32767.0 - 0.5) * 2.0);
}

float w_AND[3], w_OR[3];

void ANDgateTest() {
    int i, j, out, ERR;
    int x[3][4] = {
        {0, 0, 1, 1},
        {0, 1, 0, 1},
        {1, 1, 1, 1}  // Bias
    };
    int T[4] = {0, 0, 0, 1};
    float O, LR = 0.1, init = 0.15;

    // Inisialisasi bobot
    for (i = 0; i < 3; i++) {
        w_AND[i] = init * d_rand();
    }

    // Training Perceptron
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 4; j++) {
            O = x[0][j] * w_AND[0] + x[1][j] * w_AND[1] + x[2][j] * w_AND[2];
            out = (O > 0.0) ? 1 : 0;
            ERR = T[j] - out;

            if (ERR != 0) {
                w_AND[0] += LR * x[0][j] * ERR;
                w_AND[1] += LR * x[1][j] * ERR;
                w_AND[2] += LR * x[2][j] * ERR;
            }
        }
        printf("Percobaan AND ke : %d\n", i+1);
        printf("Error : %d\n",ERR);
    }
}

void ORgateTest() {
    int i, j, out, ERR;
    int x[3][4] = {
        {0, 0, 1, 1},
        {0, 1, 0, 1},
        {1, 1, 1, 1}  // Bias
    };
    int T[4] = {0, 1, 1, 1};
    float  O, LR = 0.1, init = 0.15;

    // Inisialisasi bobot
    for (i = 0; i < 3; i++) {
        w_OR[i] = init * d_rand();
    }

    // Training Perceptron
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 4; j++) {
            O = x[0][j] * w_OR[0] + x[1][j] * w_OR[1] + x[2][j] * w_OR[2];
            out = (O > 0.0) ? 1 : 0;
            ERR = T[j] - out;

            if (ERR != 0) {
                w_OR[0] += LR * x[0][j] * ERR;
                w_OR[1] += LR * x[1][j] * ERR;
                w_OR[2] += LR * x[2][j] * ERR;
            }
        }
        printf("Percobaan OR ke : %d\n", i+1);
        printf("Error : %d\n",ERR);
    }
}

int ANDgate (int i1, int i2) {
    int x[3][4] = {
        {0, 0, 1, 1},
        {0, 1, 0, 1},
        {1, 1, 1, 1}  // Bias
    };
    x[0][0] = i1;
    x[1][0] = i2;
    float O = x[0][0] * w_AND[0] + x[1][0] * w_AND[1] + x[2][0] * w_AND[2];
    return (O > 0.0) ? 1 : 0;
}

int ORgate (int i1, int i2) {
    int x[3][4] = {
        {0, 0, 1, 1},
        {0, 1, 0, 1},
        {1, 1, 1, 1}  // Bias
    };
    x[0][0] = i1;
    x[1][0] = i2;
    float O = x[0][0] * w_OR[0] + x[1][0] * w_OR[1] + x[2][0] * w_OR[2];
    return (O > 0.0) ? 1 : 0;
}

int main() {
    int input1, input2;

    printf("Training AND...\n");
    ANDgateTest();
    printf("\nTraining OR...\n");
    ORgateTest();
    printf("\nTraining selesai!\n\n");


    for (int i = 0; i < 4; i++) {
        printf("Input X1: ");
        scanf("%d", &input1);

        printf("Input X2: ");
        scanf("%d", &input2);

        printf("OUTPUT AND: %d\n", ANDgate(input1, input2));
        printf("OUTPUT OR:  %d\n\n", ORgate(input1, input2));
    }

    return 0;
}
