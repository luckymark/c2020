//search version
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int primes[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
const int size=(sizeof(primes))/(sizeof(int));
int two[100][2];

inline int comparator(const int *p1,const int *p2){ 
    return (*p1-*p2);
}

void searchEven(int i);
void searchOdd(int i);
int main(){
    int i;

    printf("Even Part\n");
    for(i=4;i<=100;i+=2){ 
        searchEven(i);
    }

    printf("\n\n\n\n");

    printf("Odd Part\n");
    for(i=7;i<100;i+=2){ 
        searchOdd(i);
    }

    return 0;
}
void searchEven(int x){ 
    int i,temp;
    for(i=0;i<size;++i){ 
        temp=x-primes[i];
        if(NULL!=bsearch(&temp,primes,size,sizeof(int),(int(*)(const void*,const void*))comparator)){
               two[x][0]=primes[i];
               two[x][1]=temp;  
               printf("%d = %d + %d \n",x,primes[i],temp);
               break;
        }
    }
}
void searchOdd(int x){ 
    printf("%d = %d + %d + %d\n",x,3,two[x-3][0],two[x-3][1]);
}

