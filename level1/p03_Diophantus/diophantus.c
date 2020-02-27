#include<stdio.h>
#include<math.h>
float agel=0,ageh=1000,agen,temp;
//用int会丢失精度
//agel is the lowest age
//ageh is the highest age
//agen is the median age

const float distinct=0.1;
//the deviation to bear

int main(){ 
    agen=500;
    //init
    while(1){ 
        temp=agen/6+agen/12+agen/7+5+agen/2+4-agen;
        
        if(temp<distinct&&temp>(-1*distinct))break;
        //find it

        if(temp<0){ 
            ageh=agen;
        }
        else{ 
            agel=agen;
        }
        agen=(agel+ageh)/2;
        
    }
    printf("%d",(int)round(agen));
}
//二分搜索+容许误差
