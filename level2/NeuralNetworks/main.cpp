#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "backPropagation.h"
#define LEVEL 3    //层数
#define NUMBER 16  //中间层的结点数量
#define LENGTH 8   //手写数字的大小
const char mapFile[] = "./map.txt";
const char WBFile[] = "./WB.txt";
const char testFile[] = "./test.txt";
Matrix X[LEVEL];      //激活值
Matrix W[LEVEL - 1];  //权重
Matrix B[LEVEL - 1];  //偏重
Matrix aim(10, 1);
Matrix DW[LEVEL-1],DB[LEVEL-1];
Matrix TDX[LEVEL], TDW[LEVEL - 1], TDB[LEVEL - 1];

void read();     //读入一个图到x[0]
void readTest(FILE* file);    //读入训练图
void readWB();   //读入权重和偏重，失败时随机产生
void randWB();   //随机权重和偏重
void move();     //让x[0]的值传播
void BP();       //反向传播并修改权重，偏重
void writeWB();  //记录权重和偏重
void learn();    //学习模式
void guess();    //猜测模式

int main() {
    int n;
    bool flag = true;
    printf("1 --- learn\n");
    printf("2 --- guess\n");
    while (flag) {
        scanf("%d", &n);
        switch (n) {
            case 1:
                learn();
                flag = false;
                break;
            case 2:
                guess();
                flag = false;
                break;
            default:
                break;
        }
    }
}

void learn() {
    //TODO:完善学习算法
    FILE* test = fopen(testFile,"r");
    readWB();
    if(test == nullptr) return;
    for (int i = 0; i < 10; ++i) {
        readTest(test);

        move();
        BP();
        for (int j = 0; j < LEVEL - 1; ++j) {
            DW[j] = DW[j] - TDW[j]/10.0;
            DB[j] = DB[j] - TDB[j]/10.0;
        }
    }
    for (int i = 0; i < LEVEL - 1; ++i) {
        W[i] = W[i] + (DW[i]/10.0);
        B[i] = B[i] + (DB[i]/10.0);
    }
    writeWB();
}

void guess() {
    read();
    readWB();
    move();
    Matrix pro = probability(X[LEVEL-1]);
    double max = -10;
    int num = 0;
    for (int i = 0; i < 10; ++i) {
        if (pro.value[i][0] > max){
            num = i;
            max = pro.value[i][0];
        }
    }
    printf("guess it is %d\n",num);
    printf("%lf%\n",max*100);
}

void read() {
    FILE* map = fopen(mapFile,"r");
    char str[10];
    X[0] = Matrix(LENGTH * LENGTH, 1);
    int p = 0;
    for (int i = 0; i < LENGTH; ++i) {
        fscanf(map,"%s", str);
        for (int j = 0; j < LENGTH; ++j) {
            X[0].value[p++][0] = str[j] - '0';
        }
    }
    fclose(map);
}

void readTest(FILE* file){
    int num;
    fscanf(file,"%d",&num);
    aim = Matrix(10,1);
    aim.value[num][0] = 1;
    X[0] = Matrix(LENGTH * LENGTH, 1);
    int p = 0;
    char str[10];
    for (int i = 0; i < LENGTH; ++i) {
        fscanf(file,"%s", str);
        for (int j = 0; j < LENGTH; ++j) {
            X[0].value[p++][0] = 1/(1+ exp(str[j] - '0'));//TODO
        }
    }
}

void readWB() {
    FILE* WB = fopen(WBFile, "r");
    if (WB == nullptr) {
        randWB();
    } else {
        int row,col;
        int times = (LEVEL - 1) * (LEVEL - 1);
        for (int p = 0; p < times; p++){
            fscanf(WB,"%d*%d",&row,&col);
            Matrix m(row,col);
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < col; ++j) {
                    fscanf(WB,"%lf",&m.value[i][j]);
                }
            }
            if(p % 2 == 0){
                DW[p/2] = Matrix(row,col);
                W[p/2] = m;
            }else{
                DB[p/2] = Matrix(row,col);
                B[p/2] = m;
            }
        }
    }
    fclose(WB);
}

inline double randNumber() {
    return (double)(rand() / (double)RAND_MAX) * 2 - 1;
}

void randWB() {
    Matrix w(NUMBER,LENGTH*LENGTH),b(NUMBER,1);
    DW[0] = w;
    DB[0] = b;
    for (int i = 0; i < NUMBER; ++i) {
        for (int j = 0; j < LENGTH * LENGTH; ++j) {
            w.value[i][j] = randNumber();
        }
        b.value[i][0] = randNumber();
    }
    W[0] = w;
    B[0] = b;
    w = Matrix(10,NUMBER);
    b = Matrix(10,1);
    DW[1] = w;
    DB[1] = b;
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < NUMBER; ++j) {
            w.value[i][j] = randNumber();
        }
        b.value[i][0] = randNumber();
    }
    W[1] = w;
    B[1] = b;
}

void writeWB() {
    FILE* WB = fopen(WBFile, "w");
    for (int i = 0; i < LEVEL - 1; ++i) {
        fprintf(WB, "%d*%d\n", W[i].row, W[i].col);
        for (int j = 0; j < W[i].row; ++j) {
            for (int k = 0; k < W[i].col; ++k) {
                fprintf(WB, "%lf ", W[i].value[j][k]);
            }
            fprintf(WB, "\n");
        }
        fprintf(WB, "%d*1\n", B[i].row);
        for (int j = 0; j < B[i].row; ++j) {
            fprintf(WB,"%lf\n", B[i].value[j][0]);
        }
    }
    fclose(WB);
}

void move(){
    for (int i = 0; i < LEVEL-1; ++i) {
        X[i+1] = toNext(W[i],X[i],B[i]);
    }
}

void BP(){
    TDX[LEVEL-1] = partialC2x(X[LEVEL-1],aim);
    for (int i = LEVEL-2; i >= 0; --i) {
        backPropagation(TDW[i],TDX[i],TDB[i],
                TDX[i+1],W[i],X[i],B[i]);
    }
}