#include <stdio.h>
#include<string.h>
#define  MAXLEN 1000
int flag;
//to determinate the mode
char str[MAXLEN+1];
void readMe();
int main() {
	int i;
	readMe();
    while(~scanf("%d",&flag)){
        if(flag==-1)return 0;
        scanf("%s",str);
        if(flag==1){
            for(i=0;i<strlen(str);++i){
                str[i]+=10;
                //shift 10
            }
            printf("encoded_str: %s\n\n",str);
        }
        if(flag==0){
            for(i=0;i<strlen(str);++i){
                str[i]-=10;
                //shift -10
            }
            printf("decoded_str: %s\n\n",str);
        }
    }
    return 0;
}
void readMe(){
	system("cls");
	puts("****Usage****");
	puts("1 str : encode str");
	puts("0 str : decode str");
	puts("-1 : quit\n");
}