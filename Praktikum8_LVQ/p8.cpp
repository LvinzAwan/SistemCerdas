#include <stdio.h>
#include <conio.h>
#include <math.h>

int main() {
    int i, j, k, epoh = 0, maxIter = 10;
    float alpha = 0.05f;
    float x[10][6] = {
        {1,0,0,0,1,0},
        {0,1,1,1,1,0},
        {0,0,1,0,0,1},
        {0,0,1,0,1,0},
        {0,1,0,0,0,1},
        {1,0,1,0,1,1},
        {0,0,1,1,0,0},
        {0,1,0,1,0,0},
        {1,0,0,1,0,1},
        {0,1,1,1,1,1}
    };
    int T[10] = { 1,2,1,1,1,1,2,2,2,2 };
    float w[2][6], jarak[2];

    // Inisialisasi bobot awal
    for (i = 0; i < 6; i++) {
        w[0][i] = x[0][i];
        w[1][i] = x[1][i];
    }

    // Training
    for (i = 0; i < maxIter; i++) {
        for (j = 2; j < 10; j++) {
            jarak[0] = jarak[1] = 0.0;

            for (k = 0; k < 6; k++) {
                jarak[0] += pow(x[j][k] - w[0][k], 2);
                jarak[1] += pow(x[j][k] - w[1][k], 2);
            }

            jarak[0] = sqrt(jarak[0]);
            jarak[1] = sqrt(jarak[1]);

            printf("jarak[0]: %f\n", jarak[0]);
            printf("jarak[1]: %f\n", jarak[1]);

            if (jarak[0] <= jarak[1]) {
                printf("jarak[0] lebih dekat\n");
                if (T[j] == 1) {
                    for (k = 0; k < 6; k++) {
                        w[0][k] += alpha * (x[j][k] - w[0][k]);
                        printf("w[0][%d]: %f\n", k, w[0][k]);
                    }
                } else {
                    for (k = 0; k < 6; k++) {
                        w[0][k] -= alpha * (x[j][k] - w[0][k]);
                        printf("w[0][%d]: %f\n", k, w[0][k]);
                    }
                }
            } else {
                printf("jarak[1] lebih dekat\n");
                if (T[j] == 2) {
                    for (k = 0; k < 6; k++) {
                        w[1][k] += alpha * (x[j][k] - w[1][k]);
                        printf("w[1][%d]: %f\n", k, w[1][k]);
                    }
                } else {
                    for (k = 0; k < 6; k++) {
                        w[1][k] -= alpha * (x[j][k] - w[0][k]); // Kemungkinan bug di sini
                        printf("w[1][%d]: %f\n", k, w[1][k]);
                    }
                }
            }
        }

        alpha = alpha - 0.1 * alpha; // Penurunan learning rate
        epoh++;
        printf("Epoh: %d\n", epoh);
    }

    // Running data uji
    float test[6] = {0,1,0,1,1,0};
    jarak[0] = jarak[1] = 0.0;

    for (k = 0; k < 6; k++) {
        jarak[0] += pow(test[k] - w[0][k], 2);
        jarak[1] += pow(test[k] - w[1][k], 2);
    }

    jarak[0] = sqrt(jarak[0]);
    jarak[1] = sqrt(jarak[1]);

    printf("jarak[0]: %f\n", jarak[0]);
    printf("jarak[1]: %f\n", jarak[1]);

    if (jarak[0] <= jarak[1]) {
        printf("Kelas 1\n");
    } else {
        printf("Kelas 2\n");
    }
}
