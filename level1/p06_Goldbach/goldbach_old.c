//用素数组合拼整数
#include<stdio.h>
#include<stdbool.h>

int primes[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
const int size=(sizeof(primes))/(sizeof(int));
//0-100的素数
int two[101][2];
//goldbach猜想1：大于2的偶数可分为两个素数
int three[101][3];
//goldbach猜想2：大于5的奇数可分为三个素数

void processEven();
void processOdd();
void processOddWith2();
void processOddWithout2();

void printEven();
void printOdd();

int main(){ 

    processEven();
    processOdd();

    printEven();
    printf("\n\n\n\n");
    printOdd();

    return 0;
}
void processEven(){ 
    int i,j,temp;
    for(i=0;i<size;++i){ 
        for(j=0;j<size;++j){
            temp=primes[i]+primes[j]; 
            if(temp>100)break;
            two[temp][0]=primes[i];
            two[temp][1]=primes[j];
        }
    }
}
void printEven(){ 
    int i;
    puts("even part");
    for(i=4;i<=100;i+=2){ 
            printf("%d is %d + %d\n",i,two[i][0],two[i][1]);
    }
}
void processOddWith2(){ 
    int i,j,temp;
    for(i=0;i<size;++i){ 
        for(j=0;j<size;++j){
            temp=primes[i]+primes[j]; 
            if(temp+2>100)break;
            three[temp+2][0]=2;
            three[temp+2][1]=primes[i];
            three[temp+2][2]=primes[j];
        }
    }
}
void processOddWithout2(){ 
    int i,j,temp;
    //奇数减去一个素数（除了2），一定是偶数
    for(i=4;i<100;i+=2){ 
        for(j=0;j<size;++j){ 
            temp=primes[j]+i;
            if(temp>100)break;
            three[temp][2]=primes[j];
            three[temp][0]=two[i][0];
            three[temp][1]=two[i][1];
        }
    }
}
void processOdd(){ 
    processOddWith2();
    processOddWithout2();
}
void printOdd(){ 
    int i;
    puts("odd part");
    for(i=7;i<=100;i+=2){ 
            printf("%d is %d + %d + %d\n",i,three[i][0],three[i][1],three[i][2]);
    }
}
