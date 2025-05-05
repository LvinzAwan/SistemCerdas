#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

using namespace std;

double d_rand() {
    return (((double)(rand() % 32767) / 32767.0 - 0.5) * 2.0);
}

int main() {
    srand(time(0)); 
    int i, j, k, l, bestMatch;
    double out[10], error;
    
    // Pola 7-segmen untuk angka 0-9
    int x[10][8] = {  
        {1, 1, 1, 1, 1, 1, 0, 1}, // 0
        {0, 1, 1, 0, 0, 0, 0, 1}, // 1
        {1, 1, 0, 1, 1, 0, 1, 1}, // 2
        {1, 1, 1, 1, 0, 0, 1, 1}, // 3
        {0, 1, 1, 0, 0, 1, 1, 1}, // 4
        {1, 0, 1, 1, 0, 1, 1, 1}, // 5
        {1, 0, 1, 1, 1, 1, 1, 1}, // 6
        {1, 1, 1, 0, 0, 0, 0, 1}, // 7
        {1, 1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1, 1}  // 9
    };
    
    // Target output untuk angka 0-9
    int T[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    // Inisialisasi bobot dengan tambahan bias
    double w[10][8], LR = 0.3, init = 0.5;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 8; j++) {
            w[i][j] = init * d_rand();
        }
    }

    // Training Perceptron
    for (i = 0; i < 100; i++) { // Epoch lebih tinggi
        error = 0.0;
        for (j = 0; j < 10; j++) {
            // Hitung output untuk setiap angka
            for (k = 0; k < 10; k++) {
                out[k] = 0.0;
                for (l = 0; l < 8; l++) {
                    out[k] += x[j][l] * w[k][l];
                }
            }
            
            // Pilih angka dengan aktivasi tertinggi (argmax)
            bestMatch = 0;
            for (k = 1; k < 10; k++) {
                if (out[k] > out[bestMatch]) {
                    bestMatch = k;
                }
            }

            // Error = target - prediksi
            if (bestMatch != T[j]) {
                error += 1.0;
                // Update bobot
                for (l = 0; l < 8; l++) {
                    w[T[j]][l] += LR * x[j][l]; // Perkuat target yang benar
                    w[bestMatch][l] -= LR * x[j][l]; // Melemahkan prediksi salah
                }
            }
        }
        printf("Epoch %d, Error: %.2f\n", i + 1, error / 10);
    }

    printf("\nTraining selesai!\n\n");

    // Pengujian
    int input[8];
    printf("Masukkan Input (A, B, C, D, E, F, G):\n");
    for (i = 0; i < 7; i++) {
        scanf("%d", &input[i]);
    }
    input[7] = 1; // Bias

    // Perhitungan output
    for (i = 0; i < 10; i++) {
        out[i] = 0.0;
        for (j = 0; j < 8; j++) {
            out[i] += input[j] * w[i][j];
        }
    }

    // Mencari angka dengan aktivasi tertinggi (argmax)
    bestMatch = 0;
    for (i = 1; i < 10; i++) {
        if (out[i] > out[bestMatch]) {
            bestMatch = i;
        }
    }

    printf("\nOutput: %d\n", bestMatch);
    return 0;
}
