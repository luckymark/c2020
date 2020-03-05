#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define ROUTE 0
#define WALL 1
#define BOX 3
#define AIM 4
#define CAPTURED 1
#define UNCAPTURED 0

#define L 5
#define W 10
int map[L+1][W+1];
int flag[L+1][W+1];
int x=1,y=1;
int Steps=0;



//���Ƶ�ͼ
void printmap()
{
    printf("\n"); 
    for (int i = 0; i <=L+1 ; ++i)
	{
        for (int j = 0; j <=W+1 ; ++j) {
            if (i==x&&j==y) printf("P");
            else if (map[i][j]==ROUTE) printf(" ");
            else if (map[i][j]==WALL) printf("#");
           // else if (map[i][j]==PERSON) printf("P");
            else if (map[i][j]==BOX) printf("A");
            else if (map[i][j]==AIM){
                if(flag[i][j]==UNCAPTURED)
                    printf("B");
                else
                    printf("A");
            }
        }
        printf("\n");
    }
}
int Initmap(char level)
{
    for (int i = 0; i <=L+1 ; ++i) {
        map[i][0]=WALL;
        map[i][W+1]=WALL;
    }

    for (int i = 0; i <=W+1 ; ++i) {
        map[0][i]=WALL;
        map[L+1][i]=WALL;

    }
    char str[9]= "map0.txt";
    str[3]=level;
    freopen(str,"r",stdin);
    int flagnum=0;
    for(int i=1;i<=L;i++) {
        for (int j = 1; j <= W; j++) {
            scanf("%d", &map[i][j]);
            if (map[i][j] == AIM)
                flagnum++;
        }
    }
    fclose(stdin);
    return flagnum;
}
#pragma clang diagnostic pop
void ResponseToKeydown(char ch) {
    //1����һ���ǲ���ǽ
    //2����һ�������ӣ��������ӵ���һ������ǽ
    int tx =x,ty = y;
    if (ch == 72 && map[x - 1][y] != WALL) {
        //��һ����ROUTE
        if (map[x - 1][y] == ROUTE) {
            x -= 1;
        }
        //��һ����BOX
        //���ӵ���һ��������ROUTE����AIM
        else if (map[x - 1][y] == BOX && (map[x - 2][y] == ROUTE || map[x - 2][y] == AIM)) {

            if(map[x - 2][y] == ROUTE){
                map[x-2][y]=BOX;
            }
            if(map[x-2][y] == AIM){
                flag[x-2][y]=CAPTURED;
            }
            x -= 1;
            map[x][y] = ROUTE;
        }
        //��һ����AIM
        else if (map[x - 1][y] == AIM) {
            printf("!!!!!!!!");
            //��������Ѿ���CAPTURED,������ߣ��������
            if (flag[x - 1][y] == CAPTURED) {
                //������ӵ��²���ROUTE��������,P��BOX���ƶ�
                if (map[x - 2][y] == ROUTE) {
                    flag[x - 1][y] = UNCAPTURED;
                    map[x - 2][y] = BOX;
                    x -= 1;

                }
                    //������ӵ��²���AIM
                else if (map[x - 2][y] == AIM) {
                    flag[x - 1][y] = UNCAPTURED;
                    flag[x - 2][y] = CAPTURED;
                    x -= 1;
                }
            }
                //����UNCAPTURED��ֱ������ȥ
            else if (flag[x - 1][y] == UNCAPTURED) {
                x -= 1;
            }
        }
    }
    else if (ch == 80 && map[x + 1][y] != WALL) {
        if (map[x + 1][y] == ROUTE) {
            x += 1;
        }
        else if (map[x + 1][y] == BOX && (map[x + 2][y] == ROUTE || map[x + 2][y] == AIM)) {

            if(map[x+2][y] == ROUTE){
                map[x+2][y]=BOX;
            }
            if(map[x+2][y] == AIM) {
                flag[x + 2][y] = CAPTURED;
            }
            x += 1;
            map[x][y] = ROUTE;
        }
        else if (map[x + 1][y] == AIM) {
            //��������Ѿ���CAPTURED,������ߣ��������
            if (flag[x + 1][y] == CAPTURED) {
                //������ӵ��²���ROUTE��������,P��BOX���ƶ�
                if (map[x + 2][y] == ROUTE) {
                    flag[x + 1][y] = UNCAPTURED;
                    map[x + 2][y] = BOX;
                    x += 1;

                }
                    //������ӵ��²���AIM
                else if (map[x + 2][y] == AIM) {
                    flag[x + 1][y] = UNCAPTURED;
                    flag[x + 2][y] = CAPTURED;
                    x += 1;
                }
            }
                //����UNCAPTURED��ֱ������ȥ
            else if (flag[x + 1][y] == UNCAPTURED) {
                x += 1;
            }
        }
    }
    else if (ch == 75 && map[x][y - 1] != WALL) {
        if (map[x][y - 1] == ROUTE) {
            y -= 1;
        }
        else if (map[x][y - 1] == BOX && (map[x][y - 2] == ROUTE || map[x][y - 2] == AIM)) {

            if(map[x][y-2] == ROUTE){
                map[x][y-2]=BOX;
            }
            if(map[x][y-2] == AIM) {
                flag[x][y-2] = CAPTURED;
            }
            y -= 1;
            map[x][y] = ROUTE;
        }
        else if (map[x][y - 1] == AIM) {
            //��������Ѿ���CAPTURED,������ߣ��������
            if (flag[x][y - 1] == CAPTURED) {
                //������ӵ��²���ROUTE��������,P��BOX���ƶ�
                if (map[x][y - 2] == ROUTE) {
                    flag[x][y - 1] = UNCAPTURED;
                    map[x][y - 2] = BOX;
                    y -= 1;

                }
                    //������ӵ��²���AIM
                else if (map[x][y - 2] == AIM) {
                    flag[x][y - 1] = UNCAPTURED;
                    flag[x][y - 2] = CAPTURED;
                    y -= 1;
                }
            }
                //����UNCAPTURED��ֱ������ȥ
            else if (flag[x][y - 1] == UNCAPTURED) {
                y -= 1;
            }
        }
    }
    else if (ch == 77 && map[x][y + 1] != WALL) {
        if (map[x][y + 1] == ROUTE) {
            y += 1;
        }
        else if (map[x][y + 1] == BOX && (map[x][y + 2] == ROUTE || map[x][y + 2] == AIM)) {
            if(map[x][y+2] == ROUTE){
                map[x][y+2]=BOX;
            }
            if(map[x][y+2] == AIM) {
                flag[x][y+2] =CAPTURED;
            }
            y += 1;
            map[x][y] = ROUTE;
        }
        else if (map[x][y + 1] == AIM) {
            //��������Ѿ���CAPTURED,������ߣ��������
            if (flag[x][y + 1] == CAPTURED) {
                //������ӵ��²���ROUTE��������,P��BOX���ƶ�
                if (map[x][y + 2] == ROUTE) {
                    flag[x][y + 1] = UNCAPTURED;
                    map[x][y + 2] = BOX;
                    y += 1;

                }
                    //������ӵ��²���AIM
                else if (map[x][y + 2] == AIM) {
                    flag[x][y + 1] = UNCAPTURED;
                    flag[x][y + 2] = CAPTURED;
                    y += 1;
                }
            }
                //����UNCAPTURED��ֱ������ȥ
            else if (flag[x][y + 1] == UNCAPTURED) {
                y += 1;
            }
        }
    }
    if(tx!=x||ty!=y){
        Steps+=1;
    }
}
int CountFlag()
{
    int cnt=0;
    for (int i = 1; i <=L ; ++i) {
        for (int j = 1; j <=W ; ++j) {
            if (flag[i][j]==CAPTURED)
                cnt+=1;
        }
    }
    return cnt;
}
void PrintInformation()
{
    printf("A is box��B is target location.\n");
    printf("To win the game,you need to push A to B.\n");
    printf("Enter to go on.");
    getchar();
}
void InitGame()
{
    x=1,y=1;
    Steps=0;
    memset(map,ROUTE, sizeof(map));
    memset(flag,UNCAPTURED, sizeof(flag));
}
void StartGame(char level)
{
	system("cls");
    InitGame();
    int flagnum =Initmap(level);
    char ch ;
    printmap();
    while(1)
    {
        ch=getch();
        ResponseToKeydown(ch);
        if(ch=='r')
        {
            StartGame(level);
            break;
        }


        //�����µ���Ļ
        system("cls");
        printmap();
        //�ж��Ƿ��������Ӷ��Ѿ���λ
        if(flagnum==CountFlag()){
            //��¼����
            const char *filename = "score.txt";
            FILE * file;
            file=fopen(filename,"a");
            fprintf(file,"level%c : %dsteps\n",level,Steps);
            if(level=='3'){
                printf("Great!You have finished all the levels!\n");
                printf("Enter to end the game.");
                getch();
                fprintf(file,"-----------------\n");
                break;
            }
            fclose(file);
            printf("You make it!!!\n");
            printf("You finished the first level with %d steps.\n",Steps);
            printf("(Enter to go on.)");
            getch();
            StartGame(level+1);
            break;
        }
    }
}
int main() {
    PrintInformation();
    StartGame('1');
    getchar();
    return 0;
}
