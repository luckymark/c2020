#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h> 
#include <malloc.h>
#include <string.h>
#include <algorithm>
using namespace std;

char filePath[50] = "C://Users//ZYW//temp//map.txt";
#define MAPH 100 //高
#define MAPW 100 //宽
#define PLAYERSNUMBER 10000 //每代个数
#define FATHER 50 //父代个数   //越少优化结果越好
#define GENESNUMBER 200 //gene个数，走的最多步数   //设置多了优化不了，不能太多  //不同的地图大小还需要更改
#define Evolution 200 //进化代数   //感觉后100代都没用
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
int height,width;
struct {
    int map[MAPH][MAPW];
    int startx,starty;
    int exitx,exity; 
    int height,width;   
}Map;//地图

typedef struct Player player;
struct Player{
    int x,y;
    int adapt; //适应值
    int step; //成功步数
    int gene[GENESNUMBER];
}players[PLAYERSNUMBER],sons[PLAYERSNUMBER];

struct{
    int num; //最佳路径的序号
    int adapt;//最佳路径的适应度
    int step;//最佳路径的个数
}Greatest;

void readinMap();//读进数组
void printMap();//打印地图
void born();//生成初始种群
void adaptionCal();//计算适应值
void evolution();//进化
bool cmp(player a,player b);
void printPath(player p);//打印路径


int main(){
    readinMap();
    printMap();

    clock_t start,finish;
    double duration;
    start = clock();

    born();
    adaptionCal();
    printf("%d %d\n",Greatest.step,Greatest.adapt);
    for(int i=0;i<Evolution;i++){
        evolution();
        adaptionCal();
        printf("%d %d\n",Greatest.step,Greatest.adapt);
    }
    finish = clock();
    duration = (double)(finish-start)/CLOCKS_PER_SEC;
    system("pause");
    printPath(players[Greatest.num]);
    printf("总运算时间为%fs\n",duration);
    system("pause");    
    return 0;
}

void readinMap(){ //1墙 2起点 3终点
    FILE *fp=fopen(filePath,"r");
    fscanf(fp,"size:%d*%d",&height,&width);
    Map.height=height;
    Map.width=width;
    char str[MAPW];
    for(int i=0;i<height;i++){
        fscanf(fp, "%s", str);
        for(int j=0;j<width;j++){
            switch(str[j]){
                case '0':
                    Map.map[i][j]=0;
                    break;  
                case '1':
                    Map.map[i][j]=1;
                    break;
                case '2':
                    Map.startx=i;
                    Map.starty=j;
                    Map.map[i][j]=0;
                    break;
                case '3':
                    Map.map[i][j]=3;
                    Map.exitx=i;
                    Map.exity=j;
                    break;            
                default:
                    break;
            }
        }
    }fclose(fp);
}

void born(){
    srand((unsigned)time(NULL));
    for(int i=0;i<PLAYERSNUMBER;i++){
        for(int j=0;j<GENESNUMBER;j++){
            players[i].gene[j]=rand()%4;
        }
    }
}

void adaptionCal(){ //第num个player
    Greatest.adapt=-100000;
    for(int i=0;i<PLAYERSNUMBER;i++){
        players[i].x=Map.startx;
        players[i].y=Map.starty;
        players[i].step=0;
        players[i].adapt=0;
        int tempx,tempy;
        for(int j=0;j<GENESNUMBER;j++){
            tempx=players[i].x;
            tempy=players[i].y;
            players[i].step++; //记录步数
            switch(players[i].gene[j]){
                case 0://上
                    tempx--;
                    break;
                case 3://下
                    tempx++;
                    break;
                case 2://左
                    tempy--;
                    break;
                case 1://右
                    tempy++;
                    break;                
            }
            if(j!=0&&players[i].gene[j]+players[i].gene[j-1]==3){
                players[i].adapt-=20;//走回头路
            }
            switch(Map.map[tempx][tempy]){
                case 1://墙，白走
                    players[i].adapt-=5;                    
                    break;
                case 0://可以走
                    players[i].x=tempx;
                    players[i].y=tempy;
                    break;
                case 3://到达终点
                    players[i].adapt+=100000;
                    players[i].x=tempx;
                    players[i].y=tempy;
                    break;
            }if(Map.map[tempx][tempy]==3){//到达终点
                break;
            }
        }
        if(Map.map[tempx][tempy]!=3){ //离终点的距离
            players[i].adapt-=((players[i].x-Map.exitx)*(players[i].x-Map.exitx)+(players[i].y-Map.exity)*(players[i].y-Map.exity));
        }
        if(players[i].adapt>Greatest.adapt){
            Greatest.num=i;
            Greatest.adapt=players[i].adapt;
            Greatest.step=players[i].step;
        }
    }
}

void evolution(){
    srand((unsigned)time(NULL));
    sort(players,players+PLAYERSNUMBER,cmp);
    int dad,mom;
    int num=0;//优良个体
    for(int i=0;i<PLAYERSNUMBER;i++){
        if(players[i].adapt>0){ //直接保存优良个体基因
            for(int j=0;j<GENESNUMBER;j++){
                sons[num].gene[j]=players[i].gene[j];
            }num++;
        }
    }
    for(;num<PLAYERSNUMBER;num++){ //遗传
        do{
            dad=rand()%FATHER,mom=rand()%FATHER;
        }while(dad==mom);
        int temp=rand()%GENESNUMBER;
        //这个不行
        // for(int i=0;i<GENESNUMBER;i++){
        //     sons[num].gene[i]=(players[mom].gene[i]+players[dad].gene[i])%4;
        // }

        //优化太慢了
        for(int i=0;i<temp;i++){
            sons[num].gene[i]=players[dad].gene[i];
        }for(int i=temp;i<GENESNUMBER;i++){
            sons[num].gene[i]=players[mom].gene[i];
        }
    }
    for(int i=0;i<PLAYERSNUMBER;i++){ //把基因复制到父代，含变异
        int variation=rand()%3;//每代产生的基因突变个数
        for(int j=0;j<GENESNUMBER;j++){
            players[i].gene[j]=sons[i].gene[j];
        }
        for(int j=0;j<variation;j++){
            int temp=rand()%GENESNUMBER;
            int newGene;
            do{
                newGene=rand()%4;
            }while(newGene==players[i].gene[temp]);
            players[i].gene[temp]=newGene;
        }
    }
}

void printMap(){
    for(int i=0;i<Map.height;i++){
        for(int j=0;j<Map.width;j++){
            if(Map.map[i][j]==1){
                printf("■");
            }else if(Map.map[i][j]==0){
                printf(" ");
            }else if(Map.map[i][j]==3){
                printf("o");
            }else{
                printf("▲");
            }
        }printf("\n");
    }
}

bool cmp(player a,player b){
    return a.adapt>b.adapt;
}

void setpos(int x,int y){
    COORD coord;
    coord.X=y;
    coord.Y=x;
    SetConsoleCursorPosition(handle,coord);
}

void printPath(player p){
    system("cls");
    printMap();
    setpos(Map.startx,Map.starty);
    printf("▲");
    int tempx,tempy;
    p.x=Map.startx;
    p.y=Map.starty;
    for(int i=0;i<p.step;i++){
        tempx=p.x;
        tempy=p.y;
        switch(p.gene[i]){
            case 0://上
                tempx--;
                break;
            case 3://下
                tempx++;
                break;
            case 2://左
                tempy--;
                break;
            case 1://右
                tempy++;
                break;
        }Sleep(100);

        if(Map.map[tempx][tempy]==0||Map.map[tempx][tempy]==3){
            setpos(p.x,p.y);
            printf(" ");
            p.x=tempx;
            p.y=tempy;
            setpos(p.x,p.y);
            printf("▲");
        }if(Map.map[tempx][tempy]==3){
            break;
        }        
    }setpos(height+2,0);
    printf("共用%d步\n",p.step);
    return ;
}