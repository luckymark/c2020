#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"Pushboxes.h"

extern void menu(void);
extern void scores(void);
extern void record(void);
extern void open(char sherry);
extern void putmap(void);
extern int startgame(void);

int main()
{
    int judge=0;				 // 判断是否继续进行游戏。
    menu();						 // 菜单选择关卡。
    while (1)
    {
        option=getchar();
        rewind(stdin);
        if (option == 'q')
        {
            printf(sp"You have canceled the programme...\n"sp"Bye...");
            break;
        }
        else if (option == 'x')
        {
            scores();
        }
        else if (option <= '4' && option >= '1')
        {
            open(option);
            while (1)
            {
                judge = startgame();
                if (1 == judge)
                {
                    printf("You have quited the game!\n");
                    break;
                }
                else if (2 == judge)
                {
                    open(option);
                    continue;
                }
                else
                {
                    printf("    Congratulate!\n");
                    if (rood <= steps[flag] || steps[flag] == 0)
                        steps[flag] = rood;
                    record();
                    break;
                }
            }
        }
        else
        {
            printf("\n"sp"I cann't understand your order...\n"sp"Please try it again\n");
        }
        printf(sp"Please enter any key to continue...(back to menu)");
        getchar();
        while (getchar() != '\n');
        menu();
    }
    getchar();
    return 0;
}



