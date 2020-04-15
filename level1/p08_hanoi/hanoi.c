#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 20

enum pole{
    A=0,
    B,
    C,
} ;
int n,arr[C+1][MAXSIZE+1];

void init();
void move();
int moveFrom(enum pole from);
void moveTo(int temp,enum pole to);
void hanoi(int num,enum pole from,enum pole to,enum pole mid);
inline pole2char(enum pole x){
    return (char)x+'A';
}

int main(){
    init();
    move();
    return 0;
}
void hanoi(int num,enum pole from,enum pole to,enum pole mid){
    if(1==num) {
        //move temp from2to
        int temp=moveFrom(from);
        moveTo(temp,to);
        printf("move %d from %c to %c\n",temp ,pole2char(from),pole2char(to));
        return;
    }
    hanoi(num-1,from,mid,to);
    //from -> mid 
    hanoi(1,from,to,mid);
    //from -> to
    hanoi(num-1,mid,to,from);
    //mid-> to
}
int moveFrom(enum pole from){
    return arr[from][arr[from][0]--];
}
void moveTo(int temp,enum pole to){
    arr[to][++arr[to][0]]=temp;
}
void init(){ 
    printf("Please input the number of elements: ");
    scanf("%d",&n);
    //the number of elements in A

    arr[A][0]=n;
    arr[B][0]=arr[C][0]=0;
    //use arrX[0] to count

    int i;
    for(i=1;i<=n;++i)arr[A][i]=n+1-i;
    //mark them 
}
inline void move(){ 
    printf("----Move Begin----\n");
    hanoi(n,A,C,B);
    printf("-----Move End-----");
}
