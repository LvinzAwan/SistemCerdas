#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>


//--------------------- random function -----------------------/
float  d_rand(void)
{
    return ((float)(((rand() % 32767) / 32767.0 - 0.5) * 2.0));
}
//-------------------------- sigmoid ------------------------------/
float  sigmoid(float u)
{
    return ((float)(1.0 / (1.0 + exp(-u))));
}
int main()
{
    int i, j, p, l;
    float z, delta_o, delta_h[6], g1, f1[6];
    float y[6] = { 0.0,0.0,1.0,0.0,0.0,0.0 };
    float x[11][4] = { {1.00,1.00,0.67,1.00},
       {1.00,0.67,0.67,1.00},
       {1.00,0.67,0.33,1.00},
       {1.00,0.33,0.33,1.00},
       {0.67,1.00,0.67,1.00},
       {0.67,0.67,0.67,1.00},
       {0.67,0.67,0.33,1.00},
       {0.67,0.33,0.33,1.00},
       {0.33,1.00,0.67,1.00},
       {0.33,0.67,0.33,1.00},
       {0.33,0.33,0.67,1.00} };
    float t[11] = { 1.0,1.0,1.0,0.0,1.0,1.0,1.0,0.0,1.0,0.0,1.0 };
    float w[6][4], O[6], s[6], LR = 0.1f, init = 0.15f, error;
    FILE* f;
    f = fopen("error.txt", "w");
    //inisialisasi bobot
    for (j = 0; j < 2; j++)
    {
        for (i = 0; i < 4; i++)
        {   
            w[j][i] = init * d_rand();
        }
    }
    for (j = 0; j < 3; j++)
    {
        s[j] = init * d_rand();
    }
    //training
    for (l = 0; l < 5000; l++)
    {
        error = 0.0;
        for (p = 0; p < 11; p++)
        {
            for (j = 0; j < 2; j++)
            {
                O[j] = 0.0;
                for (i = 0; i < 4; i++)
                {
                    O[j] = O[j] + x[p][i] * w[j][i];
                }
                y[j] = sigmoid(O[j]);
            }
            O[0] = 0.0;
            for (i = 0; i < 3; i++)
            {
                O[0] = O[0] + y[i] * s[i];
            }
            z = sigmoid(O[0]);
            g1 = z * (1 - z);
            delta_o = (t[p] - z) * g1;
            for (j = 0; j < 2; j++)
            {
                f1[j] = y[j] * (1 - y[j]);
            }
            for (j = 0; j < 2; j++)
            {
                delta_h[j] = f1[j] * delta_o * s[j];
            }
            for (i = 0; i < 3; i++)
            {
                s[i] = s[i] + LR * delta_o * y[i];
            }
            for (j = 0; j < 2; j++)
            {
                for (i = 0; i < 4; i++)
                {
                    w[j][i] = w[j][i] + LR * delta_h[j] * x[p][i];
                }
            }
            error = error + ((t[p] - z) * (t[p] - z)) / 2;
        }
        error = error / 11;
        printf("Iterasi: %d Error: %f\n", l, error);
        fprintf(f, "%d %f\n", l, error);
        if (error < 0.00001)break;
    }
    fclose(f);
    //running
    int x1, x2, x3;
    printf("X1=");
    scanf_s("%d", &x1);
    if(x1==3)x[0][0] = 1;
    if(x1==2)x[0][0] = 0.67;
    if(x1==1)x[0][0] = 0.33;
    printf("X2=");
    scanf_s("%d", &x2);
    if (x2 == 3)x[0][1] = 1;
    if (x2 == 2)x[0][1] = 0.67;
    if (x2 == 1)x[0][1] = 0.33;
    printf("X3=");
    scanf_s("%d", &x3);
    if (x3 == 2)x[0][2] = 0.67;
    if (x3 == 1)x[0][2] = 0.33;

    printf("IPK: %.2f\n", x[0][0]);
    printf("Psikologi: %.2f\n", x[0][1]);
    printf("Wawancara: %.2f\n", x[0][2]);
    for (j = 0; j < 2; j++)
    {
        O[j] = 0.0;
        for (i = 0; i < 4; i++)
        {
            O[j] = O[j] + x[0][i] * w[j][i];
        }
        y[j] = sigmoid(O[j]);
    }
    O[0] = 0.0;
    for (i = 0; i < 3; i++)
    {
        O[0] = O[0] + y[i] * s[i];
    }
    z = sigmoid(O[0]);
    printf("Output:%.2f\n", z);
    if (z < 0.5)
        printf("Keputusan: TIDAK LULUS\n");
    else
        printf("Keputusan: LULUS\n");
}