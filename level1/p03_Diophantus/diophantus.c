//binary search + tolerance
#include<stdio.h>
#include<math.h>

double ageL=0,ageH=1000,ageM=500,temp;
//integer can result in implicit conversion
//ageL is the lowest age
//ageH is the highest age
//ageM is the intermediate age


inline int isGood(double x){ 
    static const double distinct=0.1;
    //the deviation to bear

    return x<distinct && x>(-1*distinct);
}
inline void updateRange(){ 
    if(temp<0){ 
        ageH=ageM;
    }
    else{ 
        ageL=ageM;
    }
    ageM=(ageL+ageH)/2;
}

int main(){ 
    //binary search
    while(1){ 
        temp=ageM/6+ageM/12+ageM/7+5+ageM/2+4-ageM;
        //compute formulation deviation


        if(isGood(temp))break; 
        //found 

        updateRange();
    }
    printf("%d",(int)round(ageM));
    //四舍五入
}
