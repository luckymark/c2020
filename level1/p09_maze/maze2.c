#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include"maze.h"

void putspace(void)                      //输出空格，美化游戏。
{
    for (int i = 0; i <= 30; i++)
    {
        putchar(' ');
    }
}

void open(void)
{
    char ch;
    FILE* fp;
    if ((fp = fopen("map", "r")) == NULL)
    {
        printf("Cann't find map.txt...\nBye!");
        exit(EXIT_FAILURE);
    }
    else
    {
        for (int i = 0; i <= 19; i++)
        {
            for (int j = 0; j <= 34; j++)
            {
                ch = getc(fp);
                maze[i][j] = ch;
            }
        }
    }
}

void putmap(void)
{
    Sleep(0.5);
    system("cls");
    for (int i = 0; i <= 19; i++)
    {
        putspace();
        for (int j = 0; j <= 34; j++)
        {
            if (maze[i][j] == '0')
            {
                printf("Maze game");
            }
            else if (maze[i][j] == '1')
                putchar('#');
            else if (maze[i][j] == '2')
            {
                putchar('+');
                a = i;
                b = j;
            }
            else if (maze[i][j] == '3')
                putchar('O');
            else if (maze[i][j] == '4')
                printf("(click ↑↓←→ to move,q to quit)");
            else
                putchar(maze[i][j]);
        }
    }
    printf("\n     ");
    putspace();
}

int startgame(void)
{
    int ch;
    ch = _getch();
    while (1)
    {
        if ('q' == ch)
            return 1;
        else
        {
            ch = _getch();
            switch (ch)
            {
                case 72:
                    if (maze[a - 1][b] == ' ')
                    {
                        maze[a][b] = ' ';
                        maze[a - 1][b] = '2';
                        putmap();
                    }
                    else if (maze[a - 1][b] == '3')
                    {
                        maze[a][b] = ' ';
                        maze[a - 1][b] = '2';
                        putmap();
                        return 0;
                    }
                    break;
                case 80:
                    if (maze[a + 1][b] == ' ')
                    {
                        maze[a][b] = ' ';
                        maze[a + 1][b] = '2';
                        putmap();
                    }
                    else if (maze[a + 1][b] == '3')
                    {
                        maze[a][b] = ' ';
                        maze[a + 1][b] = '2';
                        putmap();
                        return 0;
                    }
                    break;
                case 75:
                    if (maze[a][b-1] == ' ')
                    {
                        maze[a][b] = ' ';
                        maze[a][b-1] = '2';
                        putmap();
                    }
                    else if (maze[a][b - 1] == '3')
                    {
                        maze[a][b] = ' ';
                        maze[a][b-1] = '2';
                        putmap();
                        return 0;
                    }
                    break;
                case 77:
                    if (maze[a][b+1] == ' ')
                    {
                        maze[a][b] = ' ';
                        maze[a][b+1] = '2';
                        putmap();
                    }
                    else if (maze[a][b+1] == '3')
                    {
                        maze[a][b] = ' ';
                        maze[a][b+1] = '2';
                        putmap();
                        return 0;
                    }
                    break;
                default:
                    break;
            }
        }
        ch = _getch();
    }
}