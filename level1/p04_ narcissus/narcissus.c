#include<stdio.h>
#include<stdbool.h>

int t1,t2,t3;
//temp1,temp2,temp3
bool first=true;
//to keep the pretty format

int main(){
    int i; 
    for(i=100;i<1000;++i){ 
        
        t1=i/100;
        //百位
        t2=(i/10)%10;
        //十位
        t3=i%10;
        //个位

        t1=t1*t1*t1;
        t2=t2*t2*t2;
        t3=t3*t3*t3;

        if(t1+t2+t3==i){ 
            if(first) 
                first=false;
            else 
                puts("");
            printf("%d",i);
        }
    }

    return 0;
}
