#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void decrypt(int *x,int z,int y){
    int out=0;int i;
    for(i=0;i<z;i++) {
        out = *(x + i) - y;
        if(out<32){
            out+=90;
        }
        *(x+i)=out;
    }
}
void encrypt(int *x,int z,int y){
    int out=0;int i;
    for(i=0;i<z;i++) {
        out = *(x + i) + y;
        if(out>=122){
            out=(out%122)+32;
        }
        *(x+i)=out;
    }
}
int main(){
    int length,i,key;char ch,c;int *p;
//    puts("How long string do you want to encrypt or decrypt?\n");
    scanf("%d%d\n",&length,&key);
    p=(int*)malloc(length*sizeof(int));
    for(i=0;i<length;i++){
        scanf("%c",&ch);
        *(p+i)=(int)ch;
    }
    decrypt(p,length,key);
//    encrypy(p,length,key);
    for(i=0;i<length;i++){
        c=(char)*(p+i);
        printf("%c",c);
    }
    return 0;
}
