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
    
    int x[10][8] = {  
        {1, 1, 1, 1, 1, 1, 0, 1},
        {0, 1, 1, 0, 0, 0, 0, 1},
        {1, 1, 0, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 0, 0, 1, 1},
        {0, 1, 1, 0, 0, 1, 1, 1},
        {1, 0, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 0, 1, 1, 1}  
    };
    
    int T[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    double w[10][8], LR = 0.5, init = 0.5;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 8; j++) {
            w[i][j] = init * d_rand();
        }
    }

    for (i = 0; i < 1000; i++) {
        error = 0.0;
        for (j = 0; j < 10; j++) {
            for (k = 0; k < 10; k++) {
                out[k] = 0.0;
                for (l = 0; l < 8; l++) {
                    out[k] += x[j][l] * w[k][l];
                }
            }
            
            bestMatch = 0;
            for (k = 1; k < 10; k++) {
                if (out[k] > out[bestMatch]) {
                    bestMatch = k;
                }
            }

            if (bestMatch != T[j]) {
                error += 1.0;
                for (l = 0; l < 8; l++) {
                    w[T[j]][l] += LR * x[j][l]; 
                    w[bestMatch][l] -= LR * x[j][l]; 
                }
            }
        }
        printf("Epoch %d, Error: %.2f\n", i + 1, error / 10);
    }

    printf("\nTraining selesai!\n\n");
    
    while (true) {
        int input[8];

        cout << "Masukkan Input 7-segmen (A B C D E F G) dalam satu baris (-1 untuk keluar): ";
        for (i = 0; i < 7; i++) {
            cin >> input[i];
        }

        // Jika input -1, keluar dari program
        if (input[0] == -1) {
            break;
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

        cout << "Output: " << bestMatch << "\n\n";
    }

    cout << "Terima kasih!\n";
    return 0;
}
