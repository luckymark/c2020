#include "warehouse.h"
int i=0;
int cnt=0;
int cho;
int flag=0;
int modenum=0;
store sto;
FILE*in,*out;
int main() {
    puts("1.Show inventory list\n2.Storage\n3.Out of stock\n4.exit");
    while(T){
    store*head=NULL;
    in=fopen("C:\\untitled1\\store.txt","r");
    scanf("%d",&cho);
    if(cho==4) return 0;
    head=read(head);
    head=choose(cho,head);
    out=fopen("C:\\untitled1\\store.txt","w");
//    check();
    write(head);
    }
}
