#include<stdio.h>
#include<stdbool.h>
int primes[25]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
//0-100的素数
int two[200][2];
//大于2的偶数可分为两个素数
int three[300][3];
//大于5的奇数可分为三个素数

int main(){ 
    int i;
    int j;
    int temp;
    for(i=0;i<25;++i){ 
        for(j=0;j<25;++j){
           temp=primes[i]+primes[j]; 
            two[temp][0]=primes[i];
            two[temp][1]=primes[j];

            //顺带处理奇数部分，其中一个素数为2的情况
            three[temp+2][0]=2;
            three[temp+2][1]=primes[i];
            three[temp+2][2]=primes[j];
        }
    }

    //奇数减去一个素数（除2），一定是偶数
    for(i=4;i<100;i+=2){ 
        for(j=0;j<25;++j){ 
            temp=primes[j]+i;
            three[temp][2]=primes[j];
            three[temp][0]=two[i][0];
            three[temp][1]=two[i][1];
        }
    }

    //preprocess



    puts("even part");
    for(i=4;i<=100;i+=2){ 
            printf("%d is %d + %d\n",i,two[i][0],two[i][1]);
    }
    //even
    

    printf("\n\n\n\n");
    puts("odd part");
    for(i=7;i<=100;i+=2){ 
            printf("%d is %d + %d + %d\n",i,three[i][0],three[i][1],three[i][2]);
    }
    //odd
    return 0;
}
