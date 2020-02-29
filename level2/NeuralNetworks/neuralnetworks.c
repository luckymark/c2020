#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define W1 "w1.txt"
#define B1 "b1.txt"
#define W2 "w2.txt"
#define B2 "b2.txt"
//full-connected layer's weight

#define INPUTSIZE 64
#define LAYER1SIZE 32
#define EPOCHSIZE 100000
#define FREQ 1000
#define MAXLEN 15
//max length for filename
#define LR 0.00001
//learning rate


double w1[LAYER1SIZE][INPUTSIZE],w2[10][LAYER1SIZE],b1[LAYER1SIZE],b2[10];
double tW2[10][LAYER1SIZE],tW1[LAYER1SIZE][INPUTSIZE],tB1[LAYER1SIZE],tB2[10];
//weight and grad

double ans1[LAYER1SIZE],ans2[10];
double tAns1[10],tAns2[LAYER1SIZE];
//temp and their grad

int labelNow;
double input[INPUTSIZE];
//flatten 8*8 into INPUTSIZE
double res[10];
//result----probability
double loss;
//cross_entropy_loss

inline double reLu(double x){
    return x>0?x:0;
}
//activate function
//and there is no need to backward-propagate for reLU


inline void softmax(double ans[],double res[]){
    int i;
    for(i=0;i<10;++i)ans[i]=exp(ans[i]);
    double sum=0;
    for(i=0;i<10;++i)sum+=ans[i];
    for(i=0;i<10;++i)res[i]=ans[i]/sum;
}
//compute result

inline double cross_loss(int label){
    return -1*log(res[label]);
}
//compute loss

inline void flat(char * buf,double input[]){

    FILE* fp=fopen(buf,"r");
    if(fp==NULL){ 
        printf("Cann't find or open file : %s\n",buf);
        exit(0);
    }

    int i;
    char temp;
    for(i=0;i<INPUTSIZE;++i){
        
        repeat:
        fscanf(fp,"%c",&temp);
        if(temp=='\n')
            goto repeat;
        //omit '\n'

        input[i]=(temp-'O')/9;
        //normalize
    }
    fclose(fp);
}
//flatten and normalize the input

void initialize(unsigned);
//use seed to initialize weight
void loadWeight();
void dumpWeight();

void forward(char * filename);
void backward();
//backward-propagate grad and optim weight

void epoch();
void train();
//use [0...9].txt to train
void test(char* filename);

void linear(double **ma1,double ma2[],double b[],double ma3[],int ma11,int ma12);
//full-connected layer
//ans2=W*ans1+B

int main(){
    system("cls");
    puts("Please select mode: 0 for train and 1 for test");
    char mode;
    scanf("%c",&mode);
    if(mode=='0'){
        train();
    }
    else{
        loadWeight();
        puts("Please input test-filename or quit to exit");
        char filename[MAXLEN+1];
        int i;
        while(~scanf("%s",filename)){
            if(strcmp(filename,"quit")==0)exit(0);
            test(filename);
            puts(">>Waiting for input");
        }
    }
    return 0;
}
void test(char* filename){
    forward(filename);
    int i;
    for(i=0;i<10;++i){
        if(res[i]>0.5){
            printf("\nThe tested number is %d !!!\n\n",i);
            break;
        }
    }
}
void train(){
    initialize(0);
    //init weight
                                            // loadWeight();  only for fine-tuning
    int k;
    for(k=0;k<EPOCHSIZE;++k){
        epoch();
        if(k%FREQ==0&&k!=0){
            dumpWeight();
            printf("loss: %lf\n",loss);
        }
        //frequency to save and print
    }
}
void initialize(unsigned seed){
    if(seed==0){
        //randomly set seed
        seed=time(NULL);
    }
    srand(seed);
    //set seed

    int i,j;
    for(i=0;i<LAYER1SIZE;++i){
        for(j=0;j<INPUTSIZE;++j) {
            w1[i][j] = (rand()%21-10)/10.0;
        }
    }
    for(i=0;i<10;++i){
        for(j=0;j<LAYER1SIZE;++j) {
            w2[i][j] = (rand()%21-10)/10.0;
        }
    }
    for(j=0;j<LAYER1SIZE;++j) {
        b1[j] = (rand()%21-10)/10.0;
    }
    for(j=0;j<10;++j) {
        b2[j] = (rand()%21-10)/10.0;
    }
    //init weight and normalize into [-1,1]
}
void loadWeight(){
    int i,j;
    FILE* fp=fopen(W1,"r");
    for(i=0;i<LAYER1SIZE;++i){
        for(j=0;j<INPUTSIZE;++j) {
            fscanf(fp,"%lf",&w1[i][j]);
        }
    }
    fclose(fp);
    fp=fopen(W2,"r");
    for(i=0;i<10;++i){
        for(j=0;j<LAYER1SIZE;++j) {
            fscanf(fp,"%lf",&w2[i][j]);
        }
    }
    fclose(fp);

    fp=fopen(B1,"r");
    for(j=0;j<LAYER1SIZE;++j) {
        fscanf(fp,"%lf",&b1[j]);
    }
    fclose(fp);
    fp=fopen(B2,"r");
    for(j=0;j<10;++j) {
        fscanf(fp,"%lf",&b2[j]);
    }
    fclose(fp);
}
void dumpWeight(){
    int i,j;
    FILE* fp=fopen(W1,"w");
    for(i=0;i<LAYER1SIZE;++i){
        for(j=0;j<INPUTSIZE;++j) {
            fprintf(fp,"%lf\n",w1[i][j]);
        }
    }
    fclose(fp);

    fp=fopen(W2,"w");
    for(i=0;i<10;++i){
        for(j=0;j<LAYER1SIZE;++j) {
            fprintf(fp,"%lf\n",w2[i][j]);
        }
    }
    fclose(fp);

    fp=fopen(B1,"w");
    for(j=0;j<LAYER1SIZE;++j) {
        fprintf(fp,"%lf\n",b1[j]);
    }
    fclose(fp);
    
    fp=fopen(B2,"w");
    for(j=0;j<10;++j) {
        fprintf(fp,"%lf\n",b2[j]);
    }
    fclose(fp);
}

void linear(double** ma1,double ma2[],double b[],double ma3[],int ma11,int ma12){
    //multiply and add bias
    //e.g.
    // ma1 is w1[LAYER1SIZE][INPUTSIZE] ;
    // ma2 is input[INPUTSIZE] ;
    // b is b1[LAYER1SIZE] ;
    // ma11 is LAYER1SIZE ;
    // ma12 is INPUTSIZE;

    int i,j;
    double temp;
    for(i=0;i<ma11;++i){
        temp=b[i];
        //add bias
        for(j=0;j<ma12;++j){
            temp+=*(  (double*)ma1+i*ma12+j  )*ma2[j];
            //double**->double*
        }
        //dot product
        ma3[i]=temp;
    }
}
void forward(char * filename){
    int i;
    //temp
    flat(filename,input);
    //8*8 into INPUTSIZE and normalize

    linear((double**)w1,input,b1,ans1,LAYER1SIZE,INPUTSIZE);
    //full-connected layer1

    for(i=0;i<LAYER1SIZE;++i){
        ans1[i]=reLu(ans1[i]);
    }
    //activate(reLU)


    linear((double**)w2,ans1,b2,ans2,10,LAYER1SIZE);
    //full-connected layer2

    for(i=0;i<10;++i){
        ans2[i]=reLu(ans2[i]);
    }
    //activate

    softmax(ans2,res);
    //classify
}
void epoch(){
    //batch_size==1
    int i;
    char buf[MAXLEN+1];
    for(i=0;i<10;++i){
        labelNow=i;
        sprintf(buf,"%d.txt",i);
        //filename

        forward(buf);
        loss=cross_loss(labelNow);
        backward();

    }
}
void backward(){
    //chain rule

    int i,j;
    for(i=0;i<10;++i){
        if(i==labelNow)tAns2[i]=res[i]-1;
        else tAns2[i]=res[i];
    }
    //softmax layer
    //softmax formula

    for(i=0;i<10;++i)tB2[i]=tAns2[i];
    for(i=0;i<10;++i){
        for(j=0;j<LAYER1SIZE;++j){
            tW2[i][j]=tAns2[i]*ans1[j];
        }
    }
    //full-connected layer2

    for(i=0;i<LAYER1SIZE;++i){
        tAns1[i]=0;
        for(j=0;j<10;++j){
            tAns1[i]+=tAns2[j]*w1[j][i];
        }
    }
    //temp

    for(i=0;i<LAYER1SIZE;++i)tB1[i]=tAns1[i];
    for(i=0;i<LAYER1SIZE;++i){
        for(j=0;j<INPUTSIZE;++j){
            tW1[i][j]=tAns1[i]*input[j];
        }
    }
    //full-connected layer1



    //optimize
    for(i=0;i<10;++i)b2[i]-=LR*tB2[i];
    for(i=0;i<LAYER1SIZE;++i)b1[i]-=LR*tB1[i];
    for(i=0;i<LAYER1SIZE;++i){
        for(j=0;j<INPUTSIZE;++j){
            w2[i][j]-=LR*tW2[i][j];
        }
    }
    for(i=0;i<10;++i){
        for(j=0;j<LAYER1SIZE;++j){
            w1[i][j]-=LR*tW1[i][j];
        }
    }

}
