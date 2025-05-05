#include <stdio.h>
#include <math.h>

int main() {
    // Data input
    float x[6][2] = {
        {0.10, 0.10},
        {0.20, 0.20},
        {0.30, 0.10},
        {0.50, 0.30},
        {0.40, 0.40},
        {0.20, 0.40}
    };

    // Bobot awal
    float w[2][2] = {
        {0.5, 0.5},
        {0.5, 0.5}
    };
    
    float D[2];
    int i, j, k, l;
    float lr = 0.6;

    // Training
    for (l = 0; l < 10; l++) {
        for (k = 0; k < 6; k++) {
            
            for (j = 0; j < 2; j++) {
                D[j] = sqrt(pow(w[j][0] - x[k][0], 2) + pow(w[j][1] - x[k][1], 2));
            }
            
            if (D[0] < D[1]) {
                for (i = 0; i < 2; i++) {
                    w[0][i] += lr * (x[k][i] - w[0][i]);
                }
            } else {
                for (i = 0; i < 2; i++) {
                    w[1][i] += lr * (x[k][i] - w[1][i]);
                }
            }
        }
        lr *= 0.5;
    }

    printf("Bobot akhir cluster 1: (%.4f, %.4f)\n", w[0][0], w[0][1]);
    printf("Bobot akhir cluster 2: (%.4f, %.4f)\n\n", w[1][0], w[1][1]);
    
    printf("Hasil clustering:\n");
    for (k = 0; k < 6; k++) {
        float dist1 = sqrt(pow(w[0][0] - x[k][0], 2) + pow(w[0][1] - x[k][1], 2));
        float dist2 = sqrt(pow(w[1][0] - x[k][0], 2) + pow(w[1][1] - x[k][1], 2));
        
        int cluster = (dist1 < dist2) ? 1 : 2;
        printf("Data (%.2f, %.2f) = Cluster %d\n", x[k][0], x[k][1], cluster);
    }
    
    return 0;
}
