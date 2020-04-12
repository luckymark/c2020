#include <stdio.h>
#include <synchapi.h>

static int play_x=1,play_y=1;
static int destination_x=3,destination_y=8;

static int layer7[8]={7,0,0,0,1,0,1,1};
static int layer6[8]={6,1,0,1,1,0,1,1};
static int layer5[8]={5,0,0,0,0,0,0,1};
static int layer4[8]={4,1,1,1,0,1,1,1};
static int layer3[8]={3,0,0,1,0,1,0,0};
static int layer2[8]={2,0,1,1,0,1,1,0};
static int layer1[8]={1,0,0,0,0,0,0,0};

static int wall_top[8]={8,1,1,1,1,1,1,1};
static int wall_bottom[8]={0,1,1,1,1,1,1,1};

static void drawLayer(int layer[]){
    printf("#");
    for(int i=1;i<8;i++){
        if(i==play_x && layer[0]==play_y){
            printf("▲");
            continue;
        }
        if(i==destination_x && layer[0]==destination_y){
            printf("×");
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

static int check(int x,int y){

    if(x==destination_x && y==destination_y){
        return 1;
    }
    if(x<1||x>7||y<1||y>7){
        printf("墙！不可移动！\n");
        return 0;
    }
    if(layer1[0]==y && layer1[x]==1){
        printf("墙！不可移动！\n");
        return 0;
    }
    if(layer2[0]==y && layer2[x]==1){
        printf("墙！不可移动！\n");
        return 0;
    }
    if(layer3[0]==y && layer3[x]==1){
        printf("墙！不可移动！\n");
        return 0;
    }
    if(layer4[0]==y && layer4[x]==1){
        printf("墙！不可移动！\n");
        return 0;
    }
    if(layer5[0]==y && layer5[x]==1){
        printf("墙！不可移动！\n");
        return 0;
    }
    if(layer6[0]==y && layer6[x]==1){
        printf("墙！不可移动！\n");
        return 0;
    }if(layer7[0]==y && layer7[x]==1){
        printf("墙！不可移动！\n");
        return 0;
    }
    return 1;
}

static void move(int direct){
    switch(direct){
        case 1:
            if(check(play_x+1,play_y)){
                play_x++;
            }
            break;
        case 2:
            if(check(play_x-1,play_y)){
                play_x--;
            }
            break;
        case 3:
            if(check(play_x,play_y+1)){
                play_y++;
            }
            break;
        case 4:
            if(check(play_x,play_y-1)){
                play_y--;
            }
            break;
        default:
            printf("非法输入！请重新输入！\n");
            break;
    }
}

int main(){
    int direct;

    for(;;){
        drawMaze();
        printf("选择输入：1-右移-2-左移-3-上移-4-下移-\n");
        printf("（提示：#->墙 ▲->玩家 ×->终点）\n");

        scanf("%d",&direct);
        move(direct);

        if(play_x==destination_x && play_y==destination_y){
            drawMaze();
            printf("到达终点！挑战成功！");
            return 0;
        }

        Sleep(800);
        system("cls");
    }
}