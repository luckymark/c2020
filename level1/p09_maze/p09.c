#include <stdio.h>
#include <synchapi.h>

static int play_x=1,play_y=1;
static int destination_x=3,destination_y=8;
static int layer[7][8]={{1,0,0,0,0,0,0,0},{2,0,1,1,0,1,1,0},{3,0,0,1,0,1,0,0},{4,1,1,1,0,1,1,1},{5,0,0,0,0,0,0,1},{6,1,0,1,1,0,1,1},{7,0,0,0,1,0,1,1}};
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
    for(int i=6;i>=0;i--){
        drawLayer(layer[i]);
    }
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
    for(int i=6;i>=0;i--){
        if(layer[i][0]==y && layer[i][x]==1){
            printf("墙！不可移动！\n");
            return 0;
        }
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
        scanf(" %d",&direct);
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