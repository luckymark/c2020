#include<stdio.h>
#include<stdbool.h>

int t1,t2,t3;
//temp1,temp2,temp3
bool first=true;
//for pretty format

inline void separate(int i){ 
    t1=i/100;
    //百位
    t2=(i/10)%10;
    //十位
    t3=i%10;
    //个位
}
inline int cubic(int x){ 
    return x*x*x;
}

int main(){
    int i; 
    for(i=100;i<1000;++i){ 
        //100-999

        separate(i);
        t1=cubic(t1);
        t2=cubic(t2);
        t3=cubic(t3);
        
        if(t1+t2+t3==i){ 
            if(first){ 
                first=false;
                printf("%d",i);
            }
            else 
                printf("\n%d",i);
        }
    }

    return 0;
}
