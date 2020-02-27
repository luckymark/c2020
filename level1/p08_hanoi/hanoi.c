#include<stdio.h>
#define MAXSIZE 20
int arrA[MAXSIZE+1],arrB[MAXSIZE+1],arrC[MAXSIZE+1];
void hanoi(int num,char from,char to);
int main(){
    int n;
    printf("Please input the number of elements: ");
    scanf("%d",&n);
    //the number of elements in A
    arrA[0]=n;
    arrB[0]=arrC[0]=0;
    //use arrX[0] to count

    int i;
    for(i=1;i<=n;++i)arrA[i]=n+1-i;
   	//mark it
    printf("----Move Begin----\n");
    hanoi(n,'A','C');
    printf("-----Move End-----");
    return 0;
}
void hanoi(int num,char from,char to){
    if(num==1) {
        int temp;
        //Moving temp
        //from -> to
        switch(from){
            case 'A':
                temp=arrA[arrA[0]--];
                break;
            case 'B':
                temp=arrB[arrB[0]--];
                break;
            case 'C':
                temp=arrC[arrC[0]--];
                break;
        }
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
        }
        printf("Move %d from %c to %c\n",temp ,from, to);
        return;
    }
    
    //find the other pole
    char other='A';
    //assum it as A
    if(other==from||other==to)other='B';
    if(other==from||other==to)other='C';

    hanoi(num-1,from,other);
    //from -> other
    hanoi(1,from,to);
    //from -> to
    hanoi(num-1,other,to);
    //other -> to
}
