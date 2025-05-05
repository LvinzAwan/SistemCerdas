#include <stdio.h>
#include <stdlib.h>

double d_rand(){
    return(((double)(rand()%32767)/32767.0-0.5)*2.0);
}

int main(){

    int i,j,out,ERR,y;
    int x[3][4]= {
    {0,0,1,1},
    {0,1,0,1},
    {1,1,1,1}
    };
    int T[4]={0,1,1,1};
    float w[3],O,LR=0.1,init=0.15;

    //inisialisasi bobot
    for(i=0;i<3;i++){
    w[i]=init*d_rand();
    }

    //traning
    for(i=0;i<10;i++){
    for(j=0;j<4;j++){
    O=x[0][j]*w[0]+x[1][j]*w[1]+x[2][j]*w[2];
    if(O>0.0)
    out=1;
    else
    out=0;
    ERR=T[j]-out;
    if(ERR!=0){
    w[0]=w[0]+LR*x[0][j]*ERR;
    w[1]=w[1]+LR*x[1][j]*ERR;
    w[2]=w[2]+LR*x[2][j]*ERR;
    }
    }
    printf("Err:%d\n",ERR);
    }

    //running
    for(i=0;i<4;i++){
    printf("Input X1:");
    scanf("%d",&x[0][0]);
    printf("Input X2:");
    scanf("%d",&x[1][0]);
    O=x[0][0]*w[0]+x[1][0]*w[1]+x[2][0]*w[2];
    if(O>0.0)
    y=1;
    else
    y=0;
    printf("Output:%d\n",y);
    }
}