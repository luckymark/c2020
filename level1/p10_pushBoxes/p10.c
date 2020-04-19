#include <stdio.h>
#include <synchapi.h>

static char data[3][1024];
static int theCount,count,choice,direct,score;

static int play_x,play_y;
static int box1_x,box1_y;
static int box2_x,box2_y;
static int destination1_x,destination1_y;
static int destination2_x,destination2_y;
static int layer[7][8];
static int wall_top[8]={8,1,1,1,1,1,1,1};
static int wall_bottom[8]={0,1,1,1,1,1,1,1};

static int isWall(int x,int y){
    if(x<1||x>7||y<1||y>7){
        return 1;
    }
    for(int i=6;i>=0;i--){
        if(layer[i][0]==y && layer[i][x]==1){
            return 1;
        }
    }
    return 0;
}

static int isBox(int x,int y){
    if((x==box1_x && y==box1_y) || (x==box2_x && y==box2_y)){
        return 1;
    }
    return 0;
}

static int isDestination(int x,int y){
    if((x==destination1_x && y==destination1_y) || (x==destination2_x && y==destination2_y)){
        return 1;
    }
    return 0;
}

static void move(){
    int x_add,y_add;
    switch(direct){
        case 1:
            x_add=1;
            y_add=0;
            break;
        case 2:
            x_add=-1;
            y_add=0;
            break;
        case 3:
            x_add=0;
            y_add=1;
            break;
        case 4:
            x_add=0;
            y_add=-1;
            break;
    }
    if(isWall(play_x+x_add,play_y+y_add)){
        printf("墙！不可移动！\n");
    }else{
        if(isBox(play_x+x_add,play_y+y_add)){
            if(isWall(play_x+2*x_add,play_y+2*y_add) || isBox(play_x+2*x_add,play_y+2*y_add)){
                printf("不可推动！\n");
            }else{
                if(play_x+x_add==box1_x && play_y+y_add==box1_y){
                    box1_x += x_add;
                    box1_y += y_add;
                }else{
                    box2_x += x_add;
                    box2_y += y_add;
                }
                play_x += x_add;
                play_y += y_add;
                count ++;
            }
        }else{
            play_x += x_add;
            play_y += y_add;
            count ++;
        }
    }
}

static void drawLayer(int layer[]){
    printf("#");
    for(int i=1;i<8;i++){
        if(i==play_x && layer[0]==play_y){
            printf("▲");
            continue;
        }
        if(isBox(i,layer[0])){
            printf("×");
            continue;
        }
        if(isDestination(i,layer[0])){
            printf("o");
            continue;
        }
        if(layer[i]==0){
            printf(" ");
        }else{
            printf("#");
        }
    }
    printf("#\n");
}

static void drawMaze(){
    drawLayer(wall_top);
    for(int i=6;i>=0;i--){
        drawLayer(layer[i]);
    }
    drawLayer(wall_bottom);
}

static int readData(){
    int theData=data[choice][theCount]-'0';
    theCount ++;
    return theData;
}

static void apply(){
    theCount=2;
    play_x=readData();
    play_y=readData();
    box1_x=readData();
    box1_y=readData();
    box2_x=readData();
    box2_y=readData();
    destination1_x=readData();
    destination1_y=readData();
    destination2_x=readData();
    destination2_y=readData();
    for(int i=6;i>=0;i--){
        for(int k=0;k<8;k++){
            layer[i][k]=data[choice][theCount]-'0';
            theCount ++;
        }
    }
    count=0;
}

static void writeFile(int start,int group){
    char temp[2];
    temp[0]='\0';
    temp[1]='\0';
    FILE* fpw=fopen("pushBox.txt","a+");
    for(int i=start;i<68;i++){
        temp[0]=data[group][i];
        fwrite((const void *)&temp[0],1,1,fpw);
    }
    if(group==0||group==1){
        fwrite("*",1,1,fpw);
    }
    fclose(fpw);
}

static void writeFileScore(){
    char temp[2];
    temp[0]='\0';
    temp[1]='\0';
    FILE* fpw=fopen("pushBox.txt","a+");
    itoa(score/10,temp,10);
    fwrite((const void *)&temp[0],1,1,fpw);
    itoa(score%10,temp,10);
    fwrite((const void *)&temp[0],1,1,fpw);
    fclose(fpw);
}

static void record(){
    FILE* fpw=fopen("pushBox.txt","w+");
    fclose(fpw);
    for(int i=0;i<3;i++){
        if(i==choice){
            writeFileScore();
            writeFile(2,i);
        } else{
            writeFile(0,i);
        }
    }
}

static void readFile(){
    FILE* fpr=fopen("pushBox.txt","r");
    char stream;
    int count1=0,count2=0;
    stream=fgetc(fpr);
    while(stream!=EOF){
        if(stream=='*'){
            count1 ++;
            count2 =0;
            stream=fgetc(fpr);
        }
        data[count1][count2]=stream;
        count2 ++;
        stream=fgetc(fpr);
    }
    fclose(fpr);
}

static void choose_choice(){
    for(;;){
        printf("请选择地图：1、2、3\n");
        scanf(" %d",&choice);
        if(choice==1 || choice==2 || choice==3){
            choice--;
            break;
        }else{
            printf("非法输入！请重新输入！\n");
        }
    }
}

static void choose_direct(){
    for(;;){
        printf("选择输入：1-右移-2-左移-3-上移-4-下移-\n");
        printf("（提示：#->墙 ▲->玩家 ×->箱子 o->目标位置）\n");
        scanf(" %d",&direct);
        if(direct==1||direct==2||direct==3||direct==4){
            break;
        } else{
            printf("非法输入！请重新输入！\n");
        }
    }
}

static int ifWin(){
    if(isDestination(box1_x,box1_y) && isDestination(box2_x,box2_y)){
        system("cls");
        drawMaze();
        printf("挑战成功！");
        if(100>count){
            score=100-count;
            printf("你的分数： %d",score);
        }else{
            score=0;
            printf("你的分数： %d",0);
        }
        record();
        return 1;
    } else{
        return 0;
    }
}

int main(){
    readFile();
    choose_choice();
    apply();
    for(;;){
        drawMaze();
        choose_direct();
        move();
        if(ifWin()){
            return 0;
        }
        Sleep(800);
        system("cls");
    }
}