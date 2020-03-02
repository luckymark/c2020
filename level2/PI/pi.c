#include "pi.h"
//programming according to J.Marchin formula
int main() {
    struct BigNum* piNum=getBigNum(0);
    //sum of series number

    //for every term
    struct BigNum* leftNum=getBigNum(16*5);
    struct BigNum* rightNum=getBigNum(4*239);
    struct BigNum* tempNum=getBigNum(0);
    //0 is meaningless
    int i;
    //precision increases 1.39 per iteration
    int iterationTime=(int)(ACCURACY/1.39);

    for(i=1;i<=iterationTime;++i){
        bigDiv(leftNum,5*5,leftNum);
        bigDiv(rightNum,239,rightNum);
        bigDiv(rightNum,239,rightNum);
        //239*239 is larger than MOD
        bigSub(leftNum,rightNum,tempNum);
        bigDiv(tempNum,(2*i-1),tempNum);

        if(i%2){
            //odd
            bigAdd(piNum,tempNum,piNum);
        }
        else{
            //even
            bigSub(piNum,tempNum,piNum);
        }
    }
    printNum(piNum);
    return 0;
}



void bigAdd(struct BigNum* numA,struct BigNum* numB,struct BigNum *numRes){
    int temp=MAX(numA->power,numB->power);
    int  i;
    changePower(numA,temp);
    changePower(numB,temp);

    bool carry=0;
    for(i=ACCURACY;i>=1;--i){
        numRes->digit[i]=numB->digit[i]+numA->digit[i]+carry;
        if(numRes->digit[i]>=MOD){
            numRes->digit[i]-=MOD;
            carry=1;
        }
        else carry=0;
    }
    numRes->power=temp;
    if(carry){
        for(i=ACCURACY;i>1;++i)numRes->digit[i]=numRes->digit[i-1];
        numRes->power++;
        numRes->digit[1]=0;
    }
}
void bigSub(struct BigNum* numA,struct BigNum* numB,struct BigNum *numRes){
    int temp=MAX(numA->power,numB->power);
    int i;
    changePower(numA,temp);
    changePower(numB,temp);

    bool borrow=0;
    for(i=ACCURACY;i>=1;--i){
        numRes->digit[i]=numA->digit[i]-numB->digit[i]-borrow;
        if(numRes->digit[i]<0){
            numRes->digit[i]+=MOD;
            borrow=1;
        }
        else borrow=0;
    }
    numRes->power=temp;
//    if(borrow){
//        //keep a is larger than b
//        //there is no need to write
//    }
}
void bigDiv(struct BigNum* numA,int numB,struct BigNum* numRes){
    int remain=0,i;
    for(i=1;i<=ACCURACY;++i){
        numRes->digit[i]=numA->digit[i]+remain*MOD;
        remain=numRes->digit[i]%numB;
        numRes->digit[i]/=numB;
    }
    numRes->power=numA->power;
    numRes->digit[ACCURACY-1]+=numRes->digit[ACCURACY]/MOD;
    numRes->digit[ACCURACY]%=MOD;
    if(numRes->digit[1]==0){
        numRes->power--;
        for(i=1;i<ACCURACY;++i)numRes->digit[i]=numRes->digit[i+1];
        numRes->digit[ACCURACY]=remain*MOD/numB;
    }
}
void changePower(struct BigNum* num,int target){
    //little into big
    int i, dis;
    dis=target-num->power;

    for(i=ACCURACY;i>dis;--i){
        num->digit[i]=num->digit[i-dis];
    }
    for(i=1;i<=dis;++i)num->digit[i]=0;
    num->power=target;
}

void printNum(struct BigNum* num){
    int i;
    printf("%d.",num->digit[1]);
    for(i=2;i<=SHOWLEN;++i){
        printf("%04d",num->digit[i]);
    }
    printf("\n\nEnding in %d s with precision %d\n",(int)(clock()/CLOCKS_PER_SEC),(int)log10(MOD)*ACCURACY);
    printf("Input any to quit\n");
    getch();
}
struct BigNum* getBigNum(int num){
    //in this case
    // only small number will be inputted
    struct BigNum* temp=(struct BigNum* )malloc(sizeof(struct BigNum));
    memset(temp,0,sizeof(struct BigNum));
    temp->power=1;
    temp->digit[1]=num;
    return temp;
}
