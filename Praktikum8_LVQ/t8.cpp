#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define FEATURE_SIZE 63     // Ukuran vektor fitur (9x7 = 63)
#define CLASS_COUNT 3       // Jumlah kelas (A, B, H)
#define SAMPLE_COUNT 15     // Total data sample (5 data untuk setiap kelas)
#define MAX_ITER 100        // Maksimum iterasi
#define LEARNING_RATE 0.1   // Learning rate awal

// Data training untuk huruf A (5 sampel)
int hurufA[5][FEATURE_SIZE] = {
    // Representasi biner huruf A (sampel 1 - kotak vertikal)
    {1,1,1,1,1,1,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,1,1,1,1,1,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1},
    
    // Representasi biner huruf A (sampel 2 - standar)
    {0,0,0,1,1,0,0,
     0,0,1,0,0,1,0,
     0,1,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,1,1,1,1,1,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1},
     
    // Representasi biner huruf A (sampel 3 - variasi)
    {0,0,0,1,1,0,0,
     0,0,1,0,0,1,0,
     0,1,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,1,1,1,1,1,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1},
     
    // Representasi biner huruf A (sampel 4 - bagian atas melebar)
    {0,0,1,1,1,0,0,
     0,1,0,0,0,1,0,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,1,1,1,1,1,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1},
     
    // Representasi biner huruf A (sampel 5 - lebih kotak)
    {0,0,1,1,1,0,0,
     0,1,0,0,0,1,0,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,1,1,1,1,1,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1}
};

// Data training untuk huruf B (5 sampel)
int hurufB[5][FEATURE_SIZE] = {
    // Representasi biner huruf B (sampel 1)
    {1,1,1,1,1,0,0,
     1,0,0,0,0,1,0,
     1,0,0,0,0,1,0,
     1,0,0,0,0,1,0,
     1,1,1,1,1,0,0,
     1,0,0,0,0,1,0,
     1,0,0,0,0,1,0,
     1,0,0,0,0,1,0,
     1,1,1,1,1,0,0},
    
    // Representasi biner huruf B (sampel 2 - dua kotak horizontal)
    {1,1,1,1,1,1,0,
     1,0,0,0,0,0,0,
     1,0,0,0,0,0,0,
     1,0,0,0,0,0,0,
     1,1,1,1,1,1,0,
     1,0,0,0,0,0,0,
     1,0,0,0,0,0,0,
     1,0,0,0,0,0,0,
     1,1,1,1,1,1,0},
     
    // Representasi biner huruf B (sampel 3)
    {1,1,1,1,1,0,0,
     1,0,0,0,0,1,0,
     1,0,0,0,0,0,0,
     1,0,0,0,0,0,0,
     1,1,1,1,1,0,0,
     1,0,0,0,0,1,0,
     1,0,0,0,0,0,0,
     1,0,0,0,0,0,0,
     1,1,1,1,1,0,0},
     
    // Representasi biner huruf B (sampel 4)
    {0,1,1,1,1,1,0,
     0,1,0,0,0,0,0,
     0,1,0,0,0,0,0,
     0,1,0,0,0,0,0,
     0,1,1,1,1,1,0,
     0,1,0,0,0,0,0,
     0,1,0,0,0,0,0,
     0,1,0,0,0,0,0,
     0,1,1,1,1,1,0},
     
    // Representasi biner huruf B (sampel 5 - seperti E)
    {1,1,1,1,1,0,0,
     1,0,0,0,0,1,0,
     1,0,0,0,0,0,0,
     1,0,0,0,0,0,0,
     1,1,1,1,1,0,0,
     1,0,0,0,0,0,0,
     1,0,0,0,0,0,0,
     1,0,0,0,0,0,0,
     1,1,1,1,1,0,0}
};

// Data training untuk huruf H (5 sampel)
int hurufH[5][FEATURE_SIZE] = {
    // Representasi biner huruf H (sampel 1)
    {1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,1,1,1,1,1,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1},
    
    // Representasi biner huruf H (sampel 2 - tebal)
    {1,1,0,0,0,1,1,
     1,1,0,0,0,1,1,
     1,1,0,0,0,1,1,
     1,1,0,0,0,1,1,
     1,1,1,1,1,1,1,
     1,1,0,0,0,1,1,
     1,1,0,0,0,1,1,
     1,1,0,0,0,1,1,
     1,1,0,0,0,1,1},
     
    // Representasi biner huruf H (sampel 3 - tengah tebal)
    {1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,1,1,1,1,1,1,
     1,1,1,1,1,1,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1},
     
    // Representasi biner huruf H (sampel 4 - tipis)
    {0,1,0,0,0,1,0,
     0,1,0,0,0,1,0,
     0,1,0,0,0,1,0,
     0,1,0,0,0,1,0,
     0,1,1,1,1,1,0,
     0,1,0,0,0,1,0,
     0,1,0,0,0,1,0,
     0,1,0,0,0,1,0,
     0,1,0,0,0,1,0},
     
    // Representasi biner huruf H (sampel 5 - tebal)
    {1,1,0,0,0,1,1,
     1,1,0,0,0,1,1,
     1,1,0,0,0,1,1,
     1,1,0,0,0,1,1,
     1,1,1,1,1,1,1,
     1,1,0,0,0,1,1,
     1,1,0,0,0,1,1,
     1,1,0,0,0,1,1,
     1,1,0,0,0,1,1}
};

// Data pengujian (3 sampel)
int dataUji[3][FEATURE_SIZE] = {
    // Data uji 1 (Huruf A)
    {0,0,1,1,1,0,0,
     0,1,0,0,0,1,0,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,1,1,1,1,1,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1},
     
    // Data uji 2 (Huruf B)
    {1,1,1,1,1,0,0,
     0,1,0,0,0,1,0,
     0,1,0,0,0,1,0,
     0,1,0,0,0,1,0,
     0,1,1,1,1,0,0,
     0,1,0,0,0,1,0,
     0,1,0,0,0,1,0,
     0,1,0,0,0,1,0,
     0,1,1,1,1,0,0},
     
    // Data uji 3 (Huruf H)
    {1,1,0,0,0,1,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,1,1,1,1,1,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1,
     1,0,0,0,0,0,1}
};

// Gabungkan semua data training
void combineTrainingData(float dataTraining[SAMPLE_COUNT][FEATURE_SIZE], int targets[SAMPLE_COUNT]) {
    int idx = 0;
    
    // Masukkan data huruf A
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < FEATURE_SIZE; j++) {
            dataTraining[idx][j] = (float)hurufA[i][j];
        }
        targets[idx] = 1; // Kelas 1 untuk huruf A
        idx++;
    }
    
    // Masukkan data huruf B
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < FEATURE_SIZE; j++) {
            dataTraining[idx][j] = (float)hurufB[i][j];
        }
        targets[idx] = 2; // Kelas 2 untuk huruf B
        idx++;
    }
    
    // Masukkan data huruf H
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < FEATURE_SIZE; j++) {
            dataTraining[idx][j] = (float)hurufH[i][j];
        }
        targets[idx] = 3; // Kelas 3 untuk huruf H
        idx++;
    }
}

// Cetak representasi huruf dari array biner
void cetakHuruf(int data[FEATURE_SIZE]) {
    printf("\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 7; j++) {
            if (data[i*7 + j] == 1) {
                printf("■ ");
            } else {
                printf("□ ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Fungsi untuk menguji data
void testData(float bobot[CLASS_COUNT][FEATURE_SIZE], int dataIndex) {
    float jarak[CLASS_COUNT];
    int pemenang;
    
    // Hitung jarak Euclidean untuk semua kelas
    for (int j = 0; j < CLASS_COUNT; j++) {
        jarak[j] = 0.0;
        for (int k = 0; k < FEATURE_SIZE; k++) {
            jarak[j] += pow(dataUji[dataIndex][k] - bobot[j][k], 2);
        }
        jarak[j] = sqrt(jarak[j]);
    }
    
    // Tentukan pemenang (jarak terkecil)
    pemenang = 0;
    for (int j = 1; j < CLASS_COUNT; j++) {
        if (jarak[j] < jarak[pemenang]) {
            pemenang = j;
        }
    }
    
    printf("Data Uji %d:\n", dataIndex + 1);
    cetakHuruf(dataUji[dataIndex]);
    printf("Jarak ke kelas A: %f\n", jarak[0]);
    printf("Jarak ke kelas B: %f\n", jarak[1]);
    printf("Jarak ke kelas H: %f\n", jarak[2]);
    
    // Tampilkan hasil
    printf("Hasil klasifikasi: ");
    switch (pemenang + 1) {
        case 1:
            printf("Huruf A\n");
            break;
        case 2:
            printf("Huruf B\n");
            break;
        case 3:
            printf("Huruf H\n");
            break;
        default:
            printf("Tidak dikenali\n");
    }
    printf("\n--------------------------------\n");
}

int main() {
    float dataTraining[SAMPLE_COUNT][FEATURE_SIZE];
    int targets[SAMPLE_COUNT];
    float bobot[CLASS_COUNT][FEATURE_SIZE];
    float jarak[CLASS_COUNT];
    float alpha = LEARNING_RATE;
    int epoh = 0;
    int pemenang;
    
    srand(time(NULL)); // Inisialisasi random seed
    
    // Gabungkan semua data training
    combineTrainingData(dataTraining, targets);
    
    // Inisialisasi bobot awal dengan sampel pertama dari setiap kelas
    for (int i = 0; i < FEATURE_SIZE; i++) {
        bobot[0][i] = dataTraining[0][i];  // Bobot untuk kelas A (dari sampel pertama A)
        bobot[1][i] = dataTraining[5][i];  // Bobot untuk kelas B (dari sampel pertama B)
        bobot[2][i] = dataTraining[10][i]; // Bobot untuk kelas H (dari sampel pertama H)
    }
    
    printf("=== PROGRAM LVQ UNTUK MENGENALI HURUF A, B, DAN H ===\n\n");
    printf("Training dimulai...\n");
    
    // Training
    for (int iter = 0; iter < MAX_ITER; iter++) {
        // Acak urutan data training
        for (int i = 0; i < SAMPLE_COUNT; i++) {
            int j = rand() % SAMPLE_COUNT;
            
            // Tukar data training
            for (int k = 0; k < FEATURE_SIZE; k++) {
                float temp = dataTraining[i][k];
                dataTraining[i][k] = dataTraining[j][k];
                dataTraining[j][k] = temp;
            }
            
            // Tukar target
            int tempTarget = targets[i];
            targets[i] = targets[j];
            targets[j] = tempTarget;
        }
        
        // Latih untuk setiap data
        for (int i = 0; i < SAMPLE_COUNT; i++) {
            // Hitung jarak Euclidean untuk semua kelas
            for (int j = 0; j < CLASS_COUNT; j++) {
                jarak[j] = 0.0;
                for (int k = 0; k < FEATURE_SIZE; k++) {
                    jarak[j] += pow(dataTraining[i][k] - bobot[j][k], 2);
                }
                jarak[j] = sqrt(jarak[j]);
            }
            
            // Tentukan pemenang (jarak terkecil)
            pemenang = 0;
            for (int j = 1; j < CLASS_COUNT; j++) {
                if (jarak[j] < jarak[pemenang]) {
                    pemenang = j;
                }
            }
            
            // Update bobot
            int target = targets[i];
            if (pemenang + 1 == target) { // Jika kelas yang benar
                // Bobot digerakkan mendekati data
                for (int j = 0; j < FEATURE_SIZE; j++) {
                    bobot[pemenang][j] += alpha * (dataTraining[i][j] - bobot[pemenang][j]);
                }
            } else { // Jika kelas yang salah
                // Bobot digerakkan menjauhi data
                for (int j = 0; j < FEATURE_SIZE; j++) {
                    bobot[pemenang][j] -= alpha * (dataTraining[i][j] - bobot[pemenang][j]);
                }
            }
        }
        
        // Kurangi learning rate secara bertahap
        alpha = alpha - 0.001 * alpha;
        if (alpha < 0.01) alpha = 0.01;
        
        epoh++;
        if (epoh % 10 == 0) {
            printf("Epoh: %d, Learning Rate: %f\n", epoh, alpha);
        }
    }
    
    printf("\nTraining selesai setelah %d epoh\n", epoh);
    
    // Tampilkan bobot akhir
    printf("\nBobot Akhir:\n");
    for (int i = 0; i < CLASS_COUNT; i++) {
        char kelas = 'A' + i;
        printf("Bobot kelas %c: ", kelas);
        for (int j = 0; j < 10; j++) {
            printf("%.3f ", bobot[i][j]);
        }
        printf("... (dan seterusnya)\n");
    }
    
    // Pengujian untuk ketiga data uji
    printf("\n=== PENGUJIAN ===\n");
    for (int i = 0; i < 3; i++) {
        testData(bobot, i);
    }
    
    return 0;
}