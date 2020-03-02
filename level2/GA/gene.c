#include"gene.h"
int main(){
    system("cls");
    puts("Please input maze filename");
    char buf[100];
    scanf("%s",buf);

    readMap(buf);
    printf("Your map is \n\n");
    printMap();
    evalution();
    printf("\n");
    printAns();
    return 0;
}

void readMap(char* filename){
    fp=fopen(filename,"r");
    int i,j;
    for(i=0;i<MAXN;++i){
        for(j=0;j<MAXN;++j){
            fscanf(fp,"%c",&map[i][j]);
            if(map[i][j]=='A'){
                begX=j;
                begY=i;
            }
            if(map[i][j]=='B'){
                endX=j;
                endY=i;
            }
        }
        fgetc(fp);
    }
    best=INT_MAX;
    fclose(fp);
}
void initPopulation(unsigned seed){
    if(seed==0)seed=time(NULL);
    srand(seed);
    int i,j;
    int temp;
    int last=2;
    for(i=0;i<POOLSIZE;++i){
        for(j=0;j<PATHLEN;++j){
            if(j==0||j==1){
                population[0][i].code[j][0]=1;
                population[0][i].code[j][1]=0;
                continue;
            }
            while(1){ 
                temp=rand()&3;
                if((temp+last)!=1&&(temp+last)!=5){ 
                    last=temp;
                    break;
                }
            }
            population[0][i].code[j][0]=temp>>1;
            population[0][i].code[j][1]=temp&1;
        }

    }
}
void choose(){
    int i=0;
    int j;
    float temp;
    for(i=0;i<(int)(CHOOSERATE*POOLSIZE);++i){
        temp=randFloat();
        for(j=0;j<POOLSIZE;++j){
            if(prob[j]>=temp)break;
        }
        memcpy(&population[2][i],&population[epoch&1][j],sizeof(struct Gene));
    }
}
void exchange(){
    epoch++;
    int i=0;
    int j;
    int temp,a,b;
    for(i=0;i<POOLSIZE;i+=2){
        temp=rand()%PATHLEN;
        a=rand()%(int)(CHOOSERATE*POOLSIZE);
        b=rand()%(int)(CHOOSERATE*POOLSIZE);
        for(j=0;j<PATHLEN;++j){
            if(j>temp){
                population[epoch&1][i].code[j][0]=population[2][a].code[j][0];
                population[epoch&1][i].code[j][1]=population[2][a].code[j][1];
                population[epoch&1][i+1].code[j][0]=population[2][b].code[j][0];
                population[epoch&1][i+1].code[j][1]=population[2][b].code[j][1];
            }
            else{
                population[epoch&1][i].code[j][0]=population[2][b].code[j][0];
                population[epoch&1][i].code[j][1]=population[2][b].code[j][1];
                population[epoch&1][i+1].code[j][0]=population[2][a].code[j][0];
                population[epoch&1][i+1].code[j][1]=population[2][a].code[j][1];
            }
        }
    }
}
void mutate(){
    int i,j;
    for(i=0;i<POOLSIZE;++i){
        for(j=0;j<PATHLEN;++j){
            if(randFloat()<MUTARATE){
                population[epoch&1][i].code[j][0]=1^(population[epoch&1][i].code[j][0]);
            }
            if(randFloat()<MUTARATE){
                population[epoch&1][i].code[j][1]=1^population[epoch&1][i].code[j][1];
            }

        }

    }
}
void setProb(){
    float sum=0;
    int i;
    for(i=0;i<POOLSIZE;++i){
        sum+=population[epoch&1][i].mark;
    }

    prob[0]=population[epoch&1][0].mark/sum;
    for(i=1;i<POOLSIZE;++i){
        prob[i]=prob[i-1]+population[epoch&1][i].mark/sum;
    }
    //prefix sum
}
void evalution(){
    int i,temp;
    int cnt=0;
    int t=0;
    initPopulation(7);
    float maxmark;
    while(epoch<EPOCHSIZE){
        maxmark=0;
        for(i=0;i<POOLSIZE;++i){
            maxmark=setMark(&population[epoch&1][i]);
            t++;
            if(population[epoch&1][i].reach==true){
                resIdx=i;
                temp=population[epoch&1][i].count;
                if(temp<best){
                    cnt=0;
                    best=temp;
                    continue;
                }
                if(temp==best){ 
                    cnt++;
                    if(cnt==MAXWAIT){ 
                        printf("\nEnding with %d steps in %d s\n",best,(int)(clock()/CLOCKS_PER_SEC));
                        return;
                    }
                }
            }
        }
        setProb();
        choose();
        exchange();
        mutate();
    }
}
void printMap(){
    int i,j;
    for(i=1;i<MAXN-1;++i){
        for(j=1;j<MAXN-1;++j){
            printf("%c ",map[i][j]);
        }
        printf("\n");
    }
}
void printAns(){
    struct Gene* ptr=&population[epoch&1][resIdx];
    int x,y,count;
    emulate(ptr,&x,&y,&count,true);

    printMap();
    printf("Please input any to Quit\n");
    getch();
}

int setMark(struct Gene* ptr){
    int x,y,count;
    emulate(ptr,&x,&y,&count,false);
    
    ptr->mark=(2*MAXN*MAXN-(x-endX)*(x-endX)-(y-endY)*(y-endY))-LAMBDA*count;
    //distance is basic mark
    //penalize the path length to avoid circle
    ptr->count=count;
    if(x==endX&&y==endY){ 
        ptr->reach=true;
    }
    else ptr->reach=false;
    return ptr->mark;
}
void emulate(struct Gene* ptr,int *x,int *y,int *count,bool res){ 
    int last=2;
    int cnt,temp;
    *x=begX;
    *y=begY;
    *x-=1;
    *count=1;

    for(cnt=1;cnt<PATHLEN;++cnt){
        temp=ptr->code[cnt][0]*2+ptr->code[cnt][1];
        if((last+temp)==1||(last+temp)==5)continue;
        if(*x==endX&&*y==endY)return;
        switch(temp){
            case 0: //up
                if(res){ 
                    map[*y][*x]=' ';
                    *y-=1;
                    last=0;
                    (*count)++;
                }
                else if((*y-1)>=0&&map[*y-1][*x]!='X'){
                    *y-=1;
                    last=0;
                    (*count)++;
                }
                else return;
                break;

            case 1: //down
                if(res){ 
                    map[*y][*x]=' ';
                    *y+=1;
                    last=1;
                    (*count)++;
                }
                else if((*y+1)<MAXN&&map[*y+1][*x]!='X'){
                    *y+=1;
                    last=1;
                    (*count)++;
                }
                else return;
                break;

            case 2: //left
                if(res){ 
                    map[*y][*x]=' ';
                    *x-=1;
                    last=2;
                    (*count)++;
                }
                else if((*x-1)>=0&&map[*y][*x-1]!='X'){
                    *x-=1;
                    last=2;
                    (*count)++;
                }
                else return;
                break;

            case 3: //right
                if(res){ 
                    map[*y][*x]=' ';
                    *x+=1;
                    last=3;
                    (*count)++;
                }
                else if((*x+1)<MAXN&&map[*y][*x+1]!='X'){
                    *x+=1;
                    last=3;
                    (*count)++;
                }
                else return;
                break;
        }
    }
}
