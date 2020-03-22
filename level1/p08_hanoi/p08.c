#include <stdio.h>

int move(int n,char from, char to){
    printf("plate %d from %c to %c \n",n,from,to);
    return 0;
}

int hanoi(int n,char A,char B,char C){
    if(n==1){
        move(1,A,C);
    } else {
        hanoi(n-1,A,C,B);
        move(n,A,C);
        hanoi(n-1,B,A,C);
    }
    return 0;
}

int main(){
    hanoi(64,'A','B','C');
    return 0;
}