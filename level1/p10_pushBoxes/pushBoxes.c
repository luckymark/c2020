#include <stdio.h>
#include <stdlib.h>
#include <windows.h> //光标设置的API
#include <time.h> 
#include <conio.h> //按键检测
#include <malloc.h>
#include <string.h>
// ⊙●◎○▲△☉☆★ █ ■〇▼▽△▲◆◇○◎●◢◣■


#define MAPHEIGHT 8
#define MAPWIDTH 8
#define NUM 10 //箱子最多数目
int map[MAPHEIGHT][MAPWIDTH];

int boxnum=0,desnum=0;//箱子数目
char ch; //按键
int count=0;//已经成功的箱子数
int isrestart=0;
struct p{
    int x;
    int y;
    int flag;//箱子种类
}des[NUM],box[NUM];//箱子和目的地
struct{
    int x;
    int y;
    int num; //走的次数 
}YourPosition={4,4,-1};//用户数据，应该换个名字的
int flag[4]={0};//关卡是否成功


void gotoxy(int x,int y); 
void drawMap(int map[MAPHEIGHT][MAPWIDTH],int level);//画地图
void drawYou();//画用户
void drawBox(struct p* box);//画箱子
void clean(int map[MAPHEIGHT][MAPWIDTH]);//清除上一步
void operate(int map[MAPHEIGHT][MAPWIDTH]);//处理推箱子操作
void HideCursor();//隐藏光标
int Game(int level);

int main(){
    FILE *file =NULL;
    file = fopen("C://Users//ZYW//temp//grade.txt","w");//清空
    fprintf(file,"推箱子\n");
    fclose(file);
    for(int level=1;level<5;){
        HideCursor();
        Game(level);
        if(level==4){
            break;
        }
        if(flag[0]){
            system("cls");
            break;
        }
        if(flag[level]){
            level++;
        }
    }
    printf("游戏结束\n\n");
    system("pause");
    return 0;
}


int Game(int level){
    //初始化数据
    count=0;boxnum=0;desnum=0;isrestart=0;
    YourPosition={4,4,-1};
    system("cls");
    FILE *fp=NULL;
    switch(level){
        case 1:
            fp=fopen("C://Users//ZYW//temp//map1.txt","r");
            break;
        case 2:
            fp=fopen("C://Users//ZYW//temp//map2.txt","r");
            break;
        case 3:
            fp=fopen("C://Users//ZYW//temp//map3.txt","r");
            break;
        case 4:
            printf("第4关\n敬请期待.\n\n");
            return 0;
            break;
            
    }
    for(int i=0;i<MAPHEIGHT;i++){
        for(int j=0;j<MAPWIDTH;j++){
            fscanf(fp,"%d",&map[i][j]);
        }
    }int A,B;
    fscanf(fp,"%d%d",&A,&B);
    drawMap(map,level);
    drawYou();
    while(1){
        if (isrestart){
            break;
        }
        if(_kbhit){
            operate(map);
        }
        if(count==boxnum){ //你赢了！
            gotoxy(MAPHEIGHT+3,0);
            printf("Congratulations!!!\n\n\n\n\n");
            printf("\n您最终的得分是");
            char grade;
            if(YourPosition.num<=A){
                printf("★★★");
                grade='A';
            }else if(YourPosition.num<=B){
                printf("★★");
                grade='B';
            }else {
                printf("★");
                grade='C';
            }
            FILE *filep =NULL;
            filep = fopen("C://Users//ZYW//temp//grade.txt","a+");
            fprintf(filep,"第%d关的步数为%d，星级为%c.\n",level,YourPosition.num,grade);
            fclose(filep);

            printf("\n\n按'j'再来一次");
            printf("\n\n按Space进入下一关\n\n");
            char key=getch();
            if(key!='j'){
                flag[level]=1;
            }
            break;
        }
    }
    fclose(fp);
    //走到死路还得重来
    return 0;    
}

void gotoxy(int x,int y){
    //调用win32 API去设置控制台的光标位置
    //找到控制台的这个窗口
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //光标的结构体
    COORD coord;
    //设置坐标
    coord.X=y*2; //跟想象中的矩阵不太一样，这里每个占了两个
    coord.Y=x;
    //同步到控制台
    SetConsoleCursorPosition(handle,coord);
}

void drawMap(int map[MAPHEIGHT][MAPWIDTH],int level){ //1:墙 2：箱子 3：目标 4:箱子2号 5:目标2号 
    int n,m;
    for(int i=0;i<MAPHEIGHT;i++){
        for(int j=0;j<MAPWIDTH;j++){
            switch(map[i][j]){
                case 1:
                    printf("■■");
                    break;
                case 0:
                    printf("  ");
                    break;
                case 2:
                    printf("★");//1号箱子
                    box[boxnum].x=i;
                    box[boxnum].y=j;
                    box[boxnum].flag=1;
                    boxnum++;
                    break;
                case 3:
                    printf("☆");//1号目的地
                    des[desnum]= {i,j,1}; //似乎报错了，但是可以运行 
                    desnum++;                   
                    break;
                case 4:
                    printf("◆");
                    box[boxnum]= {i,j,2};
                    boxnum++;
                    break;
                case 5:
                    printf("◇");
                    des[desnum]= {i,j,2};
                    desnum++;
                    break;

            }
        }printf("\n");
    }printf("\n您已走%2d步\n",YourPosition.num);
    printf("第%d关\n\n",level);
    printf("You are ⊙. ★&◆ are boxes. \n");
    printf("Please press 'w''s''a''d' to move.\n\n");
    printf("'j' to restart.\n'k' to game over.\n");
    return ;
}
void drawYou(){
    gotoxy(YourPosition.x,YourPosition.y);
    printf("⊙");
    YourPosition.num++;//有效按键算一次操作（推动了），只要有按键就算一次操作也可以
    gotoxy(MAPHEIGHT+1,3);
    printf("%2d",YourPosition.num);//实时更新步数
}
void drawBox(struct p* box){
    gotoxy(box->x,box->y);
    if(box->flag==1){
        printf("★");
    }else if(box->flag==2){
        printf("◆");
    }
    
}
void clean(int map[MAPHEIGHT][MAPWIDTH]){
    gotoxy(YourPosition.x,YourPosition.y);
    if(map[YourPosition.x][YourPosition.y]==3){ //如果是终点
        printf("☆");
    }else if(map[YourPosition.x][YourPosition.y]==5){
        printf("◇");
    }else printf("  ");
}

void operate(int map[MAPHEIGHT][MAPWIDTH]){ //要把地图传进去
    int tempx=YourPosition.x,tempy=YourPosition.y;//下一步
    int tempx2=YourPosition.x,tempy2=YourPosition.y;//下两步.好像可以写函数，但是我不想写==,好麻烦呀
    HideCursor();
    ch=getch(); //按键转换
    switch(ch){
        case 'j':
            isrestart=1;
            return;
        case 'k':
            flag[0]=1; //游戏结束
            isrestart=1;
            return;
        case 'w':
            tempx--; //比1.1优化了一点
            tempx2-=2;
            break;
        case 's':
            tempx++;
            tempx2+=2;
            break;
        case 'a':
            tempy--;
            tempy2-=2;
            break;
        case 'd':
            tempy++;
            tempy2+=2;
            break;
        default:
            printf("\a");
            return;
    }
    
    //只有终点和墙不会变
    if(map[tempx][tempy]==1){  //下一步是墙
        printf("\a");//over
        return;
    }else{
        for(int i=0;i<boxnum;i++){
            if(box[i].x==tempx&&box[i].y==tempy){  //下一步是箱子
                for(int j=0;j<desnum;j++){
                    if(des[j].x==tempx&&des[j].y==tempy&&des[j].flag==box[j].flag){ //箱子在终点
                        printf("\a"); //over
                        return;
                    }else if(des[j].x==tempx2&&des[j].y==tempy2&&box[i].flag==des[j].flag){  //下一步箱子在终点，太不容易了呜呜呜
                        count++;
                        box[i].x=tempx2;
                        box[i].y=tempy2;
                        clean(map);
                        YourPosition.x=tempx;
                        YourPosition.y=tempy;
                        drawYou();
                        drawBox(&box[i]); //over
                        return;
                    }
                }
                //箱子不在终点，下一步也不在终点
                if(map[tempx2][tempy2]==1){ //箱子下一步是墙
                    printf("\a");//over
                    return;
                }else{
                    for(int j=0;j<boxnum;j++){
                        if(tempx2==box[j].x&&tempy2==box[j].y){ //箱子的下一步是箱子
                            printf("\a");//over
                            return;
                        }
                    }
                    //箱子的下一步是空的，可以走
                    clean(map);
                    YourPosition.x=tempx;
                    YourPosition.y=tempy;
                    drawYou();
                    box[i].x=tempx2;
                    box[i].y=tempy2;
                    drawBox(&box[i]);//over
                    return;
                }
            }
        }
        //下一步不是箱子不是墙，可能是空的或者终点，都可以直接走
        clean(map);
        YourPosition.x=tempx;
        YourPosition.y=tempy;
        drawYou();//over
        return;
    }
    //其实总共也只有3种走的情况，如果走了原来位置还是终点还需要画上终点
 
}
void HideCursor() //隐藏光标
{
	CONSOLE_CURSOR_INFO cursor;    
	cursor.bVisible = FALSE;    
	cursor.dwSize = sizeof(cursor);    
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorInfo(handle, &cursor);
}