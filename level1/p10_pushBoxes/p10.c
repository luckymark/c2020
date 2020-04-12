#include <stdio.h>
#include <synchapi.h>

static char data[3][1024];
static int choice;
static int count=0;
static int count0;
static int direct;

static int firstScore;
static int secondScore;
static int thirdScore;

static int play_x,play_y;

static int box1_x,box1_y;
static int box2_x,box2_y;

static int destination1_x,destination1_y;
static int destination2_x,destination2_y;

static int layer7[8];
static int layer6[8];
static int layer5[8];
static int layer4[8];
static int layer3[8];
static int layer2[8];
static int layer1[8];

static int wall_top[8]={8,1,1,1,1,1,1,1};
static int wall_bottom[8]={0,1,1,1,1,1,1,1};

static int isWall(int x,int y){
    if(x<1||x>7||y<1||y>7){
        return 1;
    }
    if(layer1[0]==y && layer1[x]==1){
        return 1;
    }
    if(layer2[0]==y && layer2[x]==1){
        return 1;
    }
    if(layer3[0]==y && layer3[x]==1){
        return 1;
    }
    if(layer4[0]==y && layer4[x]==1){
        return 1;
    }
    if(layer5[0]==y && layer5[x]==1){
        return 1;
    }
    if(layer6[0]==y && layer6[x]==1){
        return 1;
    }
    if(layer7[0]==y && layer7[x]==1){
        return 1;
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
    switch(direct){
        case 1:
            if(isWall(play_x+1,play_y)){
                printf("墙！不可移动！\n");
            }else{
                if(isBox(play_x+1,play_y)){
                    if(isWall(play_x+2,play_y) || isBox(play_x+2,play_y)){
                        printf("不可推动！\n");
                    }else{
                        if(play_x+1==box1_x && play_y==box1_y){
                            box1_x++;
                        }else{
                            box2_x++;
                        }
                        play_x++;
                    }
                }else{
                    play_x++;
                }
            }
            break;
        case 2:
            if(isWall(play_x-1,play_y)){
                printf("墙！不可移动！\n");
            }else{
                if(isBox(play_x-1,play_y)){
                    if(isWall(play_x-2,play_y) || isBox(play_x-2,play_y)){
                        printf("不可推动！\n");
                    }else{
                        if(play_x-1==box1_x && play_y==box1_y){
                            box1_x--;
                        }else{
                            box2_x--;
                        }
                        play_x--;
                    }
                }else{
                    play_x--;
                }
            }
            break;
        case 3:
            if(isWall(play_x,play_y+1)){
                printf("墙！不可移动！\n");
            }else{
                if(isBox(play_x,play_y+1)){
                    if(isWall(play_x,play_y+2) || isBox(play_x,play_y+2)){
                        printf("不可推动！\n");
                    }else{
                        if(play_x==box1_x && play_y+1==box1_y){
                            box1_y++;
                        }else{
                            box2_y++;
                        }
                        play_y++;
                    }
                }else{
                    play_y++;
                }
            }
            break;
        case 4:
            if(isWall(play_x,play_y-1)){
                printf("墙！不可移动！\n");
            }else{
                if(isBox(play_x,play_y-1)){
                    if(isWall(play_x,play_y-2) || isBox(play_x,play_y-2)){
                        printf("不可推动！\n");
                    }else{
                        if(play_x==box1_x && play_y-1==box1_y){
                            box1_y--;
                        }else{
                            box2_y--;
                        }
                        play_y--;
                    }
                }else{
                    play_y--;
                }
            }
            break;
        default:
            printf("非法输入！请重新输入！\n");
            break;
    }
    count ++;
}

static void drawLayer(int layer[]){
    printf("#");
    for(int i=1;i<8;i++){
        if(i==play_x && layer[0]==play_y){
            printf("");
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
    drawLayer(layer7);
    drawLayer(layer6);
    drawLayer(layer5);
    drawLayer(layer4);
    drawLayer(layer3);
    drawLayer(layer2);
    drawLayer(layer1);
    drawLayer(wall_bottom);
}

static void score(int n){
    switch (choice){
        case 0:
            firstScore=n;
            break;
        case 1:
            secondScore=n;
            break;
        case 2:
            thirdScore=n;
            break;
        default:
            break;
    }
}

static void apply(){
    int count2=2;

    play_x=data[choice][count2]-'0';
    count2 ++;
    play_y=data[choice][count2]-'0';
    count2 ++;

    box1_x=data[choice][count2]-'0';
    count2 ++;
    box1_y=data[choice][count2]-'0';
    count2 ++;
    box2_x=data[choice][count2]-'0';
    count2 ++;
    box2_y=data[choice][count2]-'0';
    count2 ++;

    destination1_x=data[choice][count2]-'0';
    count2 ++;
    destination1_y=data[choice][count2]-'0';
    count2 ++;
    destination2_x=data[choice][count2]-'0';
    count2 ++;
    destination2_y=data[choice][count2]-'0';
    count2 ++;

    for(int k=0;k<8;k++){
        layer7[k]=data[choice][count2]-'0';
        count2 ++;
    }
    for(int k=0;k<8;k++){
        layer6[k]=data[choice][count2]-'0';
        count2 ++;
    }
    for(int k=0;k<8;k++){
        layer5[k]=data[choice][count2]-'0';
        count2 ++;
    }
    for(int k=0;k<8;k++){
        layer4[k]=data[choice][count2]-'0';
        count2 ++;
    }
    for(int k=0;k<8;k++){
        layer3[k]=data[choice][count2]-'0';
        count2 ++;
    }
    for(int k=0;k<8;k++){
        layer2[k]=data[choice][count2]-'0';
        count2 ++;
    }
    for(int k=0;k<8;k++){
        layer1[k]=data[choice][count2]-'0';
        count2 ++;
    }
}

static void record(){
    char temp[2];
    temp[0]='\0';
    temp[1]='\0';

    FILE* fpw=fopen("pushBox.txt","w+");

    switch(choice){
        case 0:

            itoa(firstScore/10,temp,10);
            fwrite((const void *)&temp[0],1,1,fpw);
            itoa(firstScore%10,temp,10);
            fwrite((const void *)&temp[0],1,1,fpw);

            for(int i=2;i<count0;i++){
                temp[0]=data[0][i];
                fwrite((const void *)&temp[0],1,1,fpw);
            }
            fwrite("*",1,1,fpw);
            for(int i=0;i<count0;i++){
                temp[0]=data[1][i];
                fwrite((const void *)&temp[0],1,1,fpw);
            }
            fwrite("*",1,1,fpw);
            for(int i=0;i<count0;i++){
                temp[0]=data[2][i];
                fwrite((const void *)&temp[0],1,1,fpw);
            }
            break;
        case 1:
            for(int i=0;i<count0;i++){
                temp[0]=data[0][i];
                fwrite((const void *)&temp[0],1,1,fpw);
            }
            fwrite("*",1,1,fpw);

            itoa(secondScore/10,temp,10);
            fwrite((const void *)&temp[0],1,1,fpw);
            itoa(secondScore%10,temp,10);
            fwrite((const void *)&temp[0],1,1,fpw);

            for(int i=2;i<count0;i++){
                temp[0]=data[1][i];
                fwrite((const void *)&temp[0],1,1,fpw);
            }
            fwrite("*",1,1,fpw);
            for(int i=0;i<count0;i++) {
                temp[0] = data[2][i];
                fwrite((const void *)&temp[0], 1, 1, fpw);
            }
            break;
        case 2:
            for(int i=0;i<count0;i++){
                temp[0]=data[0][i];
                fwrite((const void *)&temp[0],1,1,fpw);
            }
            fwrite("*",1,1,fpw);
            for(int i=0;i<count0;i++){
                temp[0]=data[1][i];
                fwrite((const void *)&temp[0],1,1,fpw);
            }
            fwrite("*",1,1,fpw);

            itoa(thirdScore/10,temp,10);
            fwrite((const void *)&temp[0],1,1,fpw);
            itoa(thirdScore%10,temp,10);
            fwrite((const void *)&temp[0],1,1,fpw);

            for(int i=2;i<count0;i++){
                temp[0]=data[2][i];
                fwrite((const void *)&temp[0],1,1,fpw);
            }
            break;
        default:
            break;
    }
    fclose(fpw);
}

int main(){

    FILE* fpr=fopen("pushBox.txt","r");
    char stream;
    int count1=0,count2=0;
    stream=fgetc(fpr);
    while(stream!=EOF){
        if(stream=='*'){
            count0=count2;
            count1 ++;
            count2 =0;
            stream=fgetc(fpr);
        }
        data[count1][count2]=stream;
        count2 ++;
        stream=fgetc(fpr);
    }
    fclose(fpr);

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

    apply();

    for(;;){
        drawMaze();
        printf("选择输入：1-右移-2-左移-3-上移-4-下移-\n");
        printf("（提示：#->墙 ▲->玩家 ×->箱子 o->目标位置）\n");

        scanf(" %d",&direct);
        move();

        if(isDestination(box1_x,box1_y) && isDestination(box2_x,box2_y)){
            system("cls");
            drawMaze();
            printf("挑战成功！");
            if(100>count){
                score(100-count);
                printf("你的分数： %d",100-count);
            }else{
                score(0);
                printf("你的分数： %d",0);
            }
            record();
            return 0;
        }

        Sleep(800);
        system("cls");
    }
}