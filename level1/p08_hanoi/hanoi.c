#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20

int n,arrA[MAXSIZE+1],arrB[MAXSIZE+1],arrC[MAXSIZE+1];

void init();
void move();
int moveFrom(char from);
void moveTo(int tmep,char to);
void hanoi(int num,char from,char to,char mid);

int main(){
    init();
    move();
    return 0;
}
void hanoi(int num,char from,char to,char mid){
    if(1==num) {
        //move temp from2to
        int temp=moveFrom(from);
        moveTo(temp,to);
        printf("move %d from %c to %c\n",temp ,from, to);
        return;
    }
    hanoi(num-1,from,mid,to);
    //from -> mid 
    hanoi(1,from,to,mid);
    //from -> to
    hanoi(num-1,mid,to,from);
    //mid-> to
}
int moveFrom(char from){ 
    switch(from){
        case 'A':
            return arrA[arrA[0]--];
        case 'B':
            return arrB[arrB[0]--];
        case 'C':
            return arrC[arrC[0]--];
        default:
            exit(-1);
    }
}
void moveTo(int temp,char to){ 
    switch(to){
        case 'A':
            arrA[++arrA[0]]=temp;
            break;
        case 'B':
            arrB[++arrB[0]]=temp;
            break;
        case 'C':
            arrC[++arrC[0]]=temp;
            break;
        default:
            exit(-1);
    }
}
void init(){ 
    printf("Please input the number of elements: ");
    scanf("%d",&n);
    //the number of elements in A

    arrA[0]=n;
    arrB[0]=arrC[0]=0;
    //use arrX[0] to count

    int i;
    for(i=1;i<=n;++i)arrA[i]=n+1-i;
    //mark them 
}
inline void move(){ 
    printf("----Move Begin----\n");
    hanoi(n,'A','C','B');
    printf("-----Move End-----");
}
