#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include"Pushboxes.h"

void readrecord(void)						//从文件中读取用户的信息。
{
    FILE* fp;
    fp = fopen("record", "r");
    for (int i = 1; i <= 4; i++)
        fscanf(fp,"%d\n",&steps[i]);
    fclose(fp);
}

void menu(void)							//游戏执行的主菜单。
{
    system("cls");
    printf("\n\n"sp"     Hello! Welcome to Pushboxes...\n");
    printf(sp"Here are 4 maps,you can click 1~4 to play.\n");
    printf(sp"If you want to check your record,you can click x.\n");
    printf(sp"If you want to quit the game,you can click q.\n");
    printf(sp"Please choose from the options above(We can only recognize the initial letter):");
}

void scores(void)						//stdout列出record文件中的内容。
{
    system("cls");
    for (int i = 1; i <= 4; i++)
    {
        printf(sp"Your least steps of map%d is %d...\n",i,steps[i]);
    }
    printf(sp"(0 steps means not played...)\n");
}

int pass(void)                           //判断是否游戏通过。
{
    int flag_ = 1;
    for (int i = 0; i <= 19; i++)
    {
        for (int j = 0; j <= 34; j++)
        {
            if (maze[i][j] == '3' || maze[i][j] == '6')
                flag_ = 0;
        }
    }
    if (flag_ == 1)
        return 1;
    else
        return 0;
}

void open(char sherry)					//根据用户的指令打开对应的map储存数据到数组maze里。
{
    char ch;
    FILE* fp = NULL;
    if (sherry == '1')
    {
        fp = fopen("map1", "r");
        flag = 1;
    }
    else if (sherry == '2')
    {
        fp = fopen("map2", "r");
        flag = 2;
    }
    else if (sherry == '3')
    {
        fp = fopen("map3", "r");
        flag = 3;
    }
    else if (sherry == '4')
    {
        fp = fopen("map4", "r");
        flag = 4;
    }
    if (fp == NULL)
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
        fclose(fp);
    }
}

void record(void)						//将用户的游戏数据写入文件。
{
    FILE* fp;
    if ((fp = fopen("record", "w")) == NULL)
    {
        printf(sp"Sorry,I cann't find your record...\n");
        printf(sp"Please enter any key to continue...(back to menu)");
    }
    else
    {
        fprintf(fp, "%d\n", steps[1]);
        fprintf(fp,"%d\n", steps[2]);
        fprintf(fp, "%d\n", steps[3]);
        fprintf(fp, "%d\n", steps[4]);
        fclose(fp);
    }
}

void putmap(void)						//在console清屏显示游戏界面。
{
    Sleep(0.5);
    system("cls");
    printf("\n\n");
    for (int i = 0; i <= 19; i++)
    {
        printf(sp);
        for (int j = 0; j <= 34; j++)
        {
            if (maze[i][j] == '0')
            {
                printf("Pushboxes game(%d)", flag);
            }
            else if (maze[i][j] == '1')
                putchar('#');
            else if (maze[i][j] == '2')
            {
                putchar('a');
                a = i;
                b = j;
            }
            else if (maze[i][j] == '3')
                putchar('O');
            else if (maze[i][j] == '4')
                printf("(click ↑↓←→ to move,q to quit,r to replay)");
            else if (maze[i][j] == '5')
                putchar('B');
            else if (maze[i][j] == '6')
            {
                putchar('@');
                a = i;
                b = j;
            }
            else if (maze[i][j] == '7')
                putchar('%');
            else if (maze[i][j] == '8')
                printf("steps:%d", rood);
            else
                putchar(maze[i][j]);
        }
    }
    printf("\n     ");
    printf(sp);
}

int startgame(void)                       //开始游戏。
{
    rood = 0;
    putmap();
    int ch;
    ch = _getch();
    while (1)
    {
        if ('q' == ch)
            return 1;
        else if ('r' == ch)
            return 2;
        else if (ch == 224)
        {
            ch = _getch();
            switch (ch)
            {
                case 72:
                    if (maze[a][b] == '2')										// 人在普通通路上走过去。
                    {
                        if (maze[a - 1][b] == ' ')								// 人走无障碍道路。
                        {
                            maze[a][b] = ' ';
                            maze[a - 1][b] = '2';
                            rood++;
                            putmap();
                        }
                        else if (maze[a - 1][b] == '3')							// 人走到箱子归位处。
                        {
                            maze[a][b] = ' ';
                            maze[a - 1][b] = '6';
                            rood++;
                            putmap();
                        }
                        else if (maze[a - 1][b] == '5' && maze[a - 2][b] == ' ')     // 人推未复位的箱子推后未复位。
                        {
                            maze[a][b] = ' ';
                            maze[a - 1][b] = '2';
                            maze[a - 2][b] = '5';
                            rood++;
                            putmap();
                        }
                        else if (maze[a - 1][b] == '5' && maze[a - 2][b] == '3')     // 人推未复位的箱子推后复位。
                        {
                            maze[a][b] = ' ';
                            maze[a - 1][b] = '2';
                            maze[a - 2][b] = '7';
                            rood++;
                            putmap();
                        }
                        else if (maze[a - 1][b] == '7' && maze[a - 2][b] == ' ')	// 人推已复位的箱子。
                        {
                            maze[a][b] == ' ';
                            maze[a - 1][b] = '6';
                            maze[a - 2][b] = '3';
                            rood++;
                            putmap();
                        }
                    }
                    else if (maze[a][b] == '6')									// 人从箱子归位处走出去。
                    {
                        if (maze[a - 1][b] == ' ')								// 人走无障碍道路。
                        {
                            maze[a][b] = '3';
                            maze[a - 1][b] = '2';
                            rood++;
                            putmap();
                        }
                        else if (maze[a - 1][b] == '3')							// 人走到箱子归位处。
                        {
                            maze[a][b] = '3';
                            maze[a - 1][b] = '6';
                            rood++;
                            putmap();
                        }
                        else if (maze[a - 1][b] == '5' && maze[a - 2][b] == ' ')     // 人推未复位的箱子推后未复位。
                        {
                            maze[a][b] = '3';
                            maze[a - 1][b] = '2';
                            maze[a - 2][b] = '5';
                            rood++;
                            putmap();
                        }
                        else if (maze[a - 1][b] == '5' && maze[a - 2][b] == '3')     // 人推未复位的箱子推后复位。
                        {
                            maze[a][b] = '3';
                            maze[a - 1][b] = '2';
                            maze[a - 2][b] = '7';
                            rood++;
                            putmap();
                        }
                        else if (maze[a - 1][b] == '7' && maze[a - 2][b] == ' ')	// 人推已复位的箱子。
                        {
                            maze[a][b] == '3';
                            maze[a - 1][b] = '6';
                            maze[a - 2][b] = '3';
                            rood++;
                            putmap();
                        }
                    }
                    if (pass())
                        return 0;
                    break;
                case 80:
                    if (maze[a][b] == '2')
                    {
                        if (maze[a + 1][b] == ' ')								// 人走无障碍道路。
                        {
                            maze[a][b] = ' ';
                            maze[a + 1][b] = '2';
                            rood++;
                            putmap();
                        }
                        else if (maze[a + 1][b] == '3')							// 人走到箱子归位处。
                        {
                            maze[a][b] = ' ';
                            maze[a + 1][b] = '6';
                            rood++;
                            putmap();
                        }
                        else if (maze[a + 1][b] == '5' && maze[a + 2][b] == ' ')     // 人推未复位的箱子推后未复位。
                        {
                            maze[a][b] = ' ';
                            maze[a + 1][b] = '2';
                            maze[a + 2][b] = '5';
                            rood++;
                            putmap();
                        }
                        else if (maze[a + 1][b] == '5' && maze[a + 2][b] == '3')     // 人推未复位的箱子推后复位。
                        {
                            maze[a][b] = ' ';
                            maze[a + 1][b] = '2';
                            maze[a + 2][b] = '7';
                            rood++;
                            putmap();
                        }
                        else if (maze[a + 1][b] == '7' && maze[a + 2][b] == ' ')	// 人推已复位的箱子。
                        {
                            maze[a][b] == ' ';
                            maze[a + 1][b] = '6';
                            maze[a + 2][b] = '3';
                            rood++;
                            putmap();
                        }
                    }
                    else if (maze[a][b] == '6')
                    {
                        if (maze[a + 1][b] == ' ')								// 人走无障碍道路。
                        {
                            maze[a][b] = '3';
                            maze[a + 1][b] = '2';
                            rood++;
                            putmap();
                        }
                        else if (maze[a + 1][b] == '3')							// 人走到箱子归位处。
                        {
                            maze[a][b] = '3';
                            maze[a + 1][b] = '6';
                            rood++;
                            putmap();
                        }
                        else if (maze[a + 1][b] == '5' && maze[a + 2][b] == ' ')     // 人推未复位的箱子推后未复位。
                        {
                            maze[a][b] = '3';
                            maze[a + 1][b] = '2';
                            maze[a + 2][b] = '5';
                            rood++;
                            putmap();
                        }
                        else if (maze[a + 1][b] == '5' && maze[a + 2][b] == '3')     // 人推未复位的箱子推后复位。
                        {
                            maze[a][b] = '3';
                            maze[a + 1][b] = '2';
                            maze[a + 2][b] = '7';
                            rood++;
                            putmap();
                        }
                        else if (maze[a + 1][b] == '7' && maze[a + 2][b] == ' ')	// 人推已复位的箱子。
                        {
                            maze[a][b] == '3';
                            maze[a + 1][b] = '6';
                            maze[a + 2][b] = '3';
                            rood++;
                            putmap();
                        }
                    }
                    if (pass())
                        return 0;
                    break;
                case 75:
                    if (maze[a][b] == '2')
                    {
                        if (maze[a][b - 1] == ' ')								// 人走无障碍道路。
                        {
                            maze[a][b] = ' ';
                            maze[a][b - 1] = '2';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b - 1] == '3')							// 人走到箱子归位处。
                        {
                            maze[a][b] = ' ';
                            maze[a][b - 1] = '6';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b - 1] == '5' && maze[a][b - 2] == ' ')     // 人推未复位的箱子推后未复位。
                        {
                            maze[a][b] = ' ';
                            maze[a][b - 1] = '2';
                            maze[a][b - 2] = '5';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b - 1] == '5' && maze[a][b - 2] == '3')     // 人推未复位的箱子推后复位。
                        {
                            maze[a][b] = ' ';
                            maze[a][b - 1] = '2';
                            maze[a][b - 2] = '7';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b - 1] == '7' && maze[a][b - 2] == ' ')	// 人推已复位的箱子。
                        {
                            maze[a][b] == ' ';
                            maze[a][b - 1] = '6';
                            maze[a][b - 2] = '3';
                            rood++;
                            putmap();
                        }
                    }
                    else if (maze[a][b] == '6')
                    {
                        if (maze[a][b - 1] == ' ')								// 人走无障碍道路。
                        {
                            maze[a][b] = '3';
                            maze[a][b - 1] = '2';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b - 1] == '3')							// 人走到箱子归位处。
                        {
                            maze[a][b] = '3';
                            maze[a][b - 1] = '6';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b - 1] == '5' && maze[a][b - 2] == ' ')     // 人推未复位的箱子推后未复位。
                        {
                            maze[a][b] = '3';
                            maze[a][b - 1] = '2';
                            maze[a][b - 2] = '5';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b - 1] == '5' && maze[a][b - 2] == '3')     // 人推未复位的箱子推后复位。
                        {
                            maze[a][b] = '3';
                            maze[a][b - 1] = '2';
                            maze[a][b - 2] = '7';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b - 1] == '7' && maze[a][b - 2] == ' ')	// 人推已复位的箱子。
                        {
                            maze[a][b] == '3';
                            maze[a][b - 1] = '6';
                            maze[a][b - 2] = '3';
                            rood++;
                            putmap();
                        }
                    }
                    if (pass())
                        return 0;
                    break;
                case 77:
                    if (maze[a][b] == '2')
                    {
                        if (maze[a][b + 1] == ' ')								// 人走无障碍道路。
                        {
                            maze[a][b] = ' ';
                            maze[a][b + 1] = '2';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b + 1] == '3')							// 人走到箱子归位处。
                        {
                            maze[a][b] = ' ';
                            maze[a][b + 1] = '6';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b + 1] == '5' && maze[a][b + 2] == ' ')     // 人推未复位的箱子推后未复位。
                        {
                            maze[a][b] = ' ';
                            maze[a][b + 1] = '2';
                            maze[a][b + 2] = '5';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b + 1] == '5' && maze[a][b + 2] == '3')     // 人推未复位的箱子推后复位。
                        {
                            maze[a][b] = ' ';
                            maze[a][b + 1] = '2';
                            maze[a][b + 2] = '7';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b + 1] == '7' && maze[a][b + 2] == ' ')	// 人推已复位的箱子。
                        {
                            maze[a][b] == ' ';
                            maze[a][b + 1] = '6';
                            maze[a][b + 2] = '3';
                            rood++;
                            putmap();
                        }
                    }
                    else if (maze[a][b] == '6')
                    {
                        if (maze[a][b + 1] == ' ')								// 人走无障碍道路。
                        {
                            maze[a][b] = '3';
                            maze[a][b + 1] = '2';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b + 1] == '3')							// 人走到箱子归位处。
                        {
                            maze[a][b] = '3';
                            maze[a][b + 1] = '6';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b + 1] == '5' && maze[a][b + 2] == ' ')     // 人推未复位的箱子推后未复位。
                        {
                            maze[a][b] = '3';
                            maze[a][b + 1] = '2';
                            maze[a][b + 2] = '5';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b + 1] == '5' && maze[a][b + 2] == '3')     // 人推未复位的箱子推后复位。
                        {
                            maze[a][b] = '3';
                            maze[a][b + 1] = '2';
                            maze[a][b + 2] = '7';
                            rood++;
                            putmap();
                        }
                        else if (maze[a][b + 1] == '7' && maze[a][b + 2] == ' ')	// 人推已复位的箱子。
                        {
                            maze[a][b] == '3';
                            maze[a][b + 1] = '6';
                            maze[a][b + 2] = '3';
                            rood++;
                            putmap();
                        }
                    }
                    if (pass())
                        return 0;
                    break;
                default:
                    break;
            }
        }
        ch = _getch();
    }
}
