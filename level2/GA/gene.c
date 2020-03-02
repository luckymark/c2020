#include"gene.h"
int main(){
    system("cls");
    puts("Please input maze filename");
    char buf[100];
    scanf("%s",buf);

    readMap(buf);
    printf("Your map is \n\n");
    printMap();
    //show your map

    evalution();
    //main function

    printf("\n");
    printAns();
    //show my solution
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
                //mark begin
            }
            if(map[i][j]=='B'){
                endX=j;
                endY=i;
                //mark end
            }
        }
        fgetc(fp);
        //get '\n'
    }
    fclose(fp);
}
void initPopulation(unsigned seed){
    if(seed==0)seed=time(NULL);
    srand(seed);
    //seed

    int i,j,temp;
    int last=2;
    //last==left
    for(i=0;i<POOLSIZE;++i){
        for(j=0;j<PATHLEN;++j){
            if(j==0||j==1){
                //first and second step must be left
                population[0][i].code[j][0]=1;
                population[0][i].code[j][1]=0;
                continue;
            }
            while(1){ 
                temp=rand()&3;
                if((temp+last)!=1&&(temp+last)!=5){ 
                    //不直接走回头路
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
    int i=0,j;
    float temp;
    for(i=0;i<(int)(CHOOSERATE*POOLSIZE);++i){
        temp=randFloat();
        for(j=0;j<POOLSIZE;++j){
            if(prob[j]>=temp)break;
            //选择第一个对应概率和大于等于阈值的gene
        }

        memcpy(&population[2][i],&population[epoch&1][j],sizeof(struct Gene));
        //choose into good population
    }
}
void exchange(){
    //cross gene

    epoch++;
    //next epoch
    int i=0,j;
    int temp,a,b;
    for(i=0;i<POOLSIZE;i+=2){
        //two children
        temp=rand()%PATHLEN;
        a=rand()%(int)(CHOOSERATE*POOLSIZE);
        b=rand()%(int)(CHOOSERATE*POOLSIZE);
        //randomly choose parents
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
                population[epoch&1][i].code[j][0]=~(population[epoch&1][i].code[j][0]);
            }
            if(randFloat()<MUTARATE){
                population[epoch&1][i].code[j][1]=~(population[epoch&1][i].code[j][1]);
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

    //初始化
    initPopulation(7);
    //lucky number
    
    //打分
    while(epoch<EPOCHSIZE){
        
        for(i=0;i<POOLSIZE;++i){

            setMark(&population[epoch&1][i]);
            if(population[epoch&1][i].reach==true){
                resIdx=i;
                //record solution
                temp=population[epoch&1][i].count;
                //path_length
                if(temp<best){
                    cnt=0;
                    //相同的局部最优解出现次数
                    best=temp;
                    continue;
                }
                if(temp==best){ 
                    cnt++;
                    if(cnt==MAXWAIT){ 
                        //局部解视为最优解
                        printf("\nEnding with %d in %d s\n",best,(int)(clock()/CLOCKS_PER_SEC));
                        return;
                    }
                }
            }
        }
        
        //轮盘赌
        setProb();
        //选择优势种群
        choose();
        //交换
        exchange();
        //变异
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
    int x=begX,y=begY;
    int last=2;
    int temp,i,j;
    x-=2;
    //the first and second steps
    for(i=2;i<PATHLEN;++i){
        if(x==endX&&y==endY){ 
            break;
        }
        temp=ptr->code[i][0]*2+ptr->code[i][1];
        if((last+temp)==1||(last+temp)==5)continue;
        map[y][x]=' ';
        //redraw path
        switch(temp){
            case 0: //up
                y-=1;
                last=0;
                break;
            case 1: //down
                y+=1;
                last=1;
                break;
            case 2: //left
                x-=1;
                last=2;
                break;
            case 3: //right
                x+=1;
                last=3;
                break;
        }

    }
    printMap();
    printf("Please input any to Quit\n");
    getch();
}

int setMark(struct Gene* ptr){
    //这里模拟不想封装函数
    //因为感觉虽然大致一致，但是前面的部分不用考虑是否合法，并且要覆盖原图，与后者还是有很多区别
    int last=2;
    int count=0;
    //0 is higher than 1
    int x=begX,y=begY;
    int cnt,temp;
    x-=2;
    for(cnt=2;cnt<PATHLEN;++cnt){
        temp=ptr->code[cnt][0]*2+ptr->code[cnt][1];
        if((last+temp)==1||(last+temp)==5)continue;
        if(x==endX&&y==endY)goto end;
        switch(temp){
            case 0: //up
                if((y-1)>=0&&map[y-1][x]!='X'){
                    y-=1;
                    last=0;
                    count++;
                }
                else goto end;
                break;

            case 1: //down
                if((y+1)<MAXN&&map[y+1][x]!='X'){
                    y+=1;
                    last=1;
                    count++;
                }
                else goto end;
                break;

            case 2: //left
                if((x-1)>=0&&map[y][x-1]!='X'){
                    x-=1;
                    last=2;
                    count++;
                }
                else goto end;
                break;

            case 3: //right
                if((x+1)<MAXN&&map[y][x+1]!='X'){
                    x+=1;
                    last=3;
                    count++;
                }
                else goto end;
                break;
        }
    }
end:

    //前面是模拟
    //真正打分
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
