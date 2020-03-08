//
// Created by surfaceCS on 2020/3/8.
//

#include<stdio.h>
#include"warehouse.h"
#include<Windows.h>
#include<string.h>

int main()
{
    char ch;
    printf("\n\tHello!Welcome to the warehouse management system!");
    getchar();
    rewind(stdin);
    Good* head=NULL;
    while (1)
    {
        head = Readgood(head);
        Menu();
        ch = getchar();
        rewind(stdin);
        if (ch == 'a' || ch == 'A')
        {
            Showgood(head);
        }
        else if (ch == 'b' || ch == 'B')
        {
            head = putin(head);
        }
        else if (ch == 'c' || ch == 'C')
        {
            head = takeout(head);
        }
        else if (ch == 'q' || ch == 'Q')
        {
            printf("\n\t...\n\tYou have quit the programme...\n");
            Emptythelist(head);
            exit(0);
        }
        else
            puts("\tI can't understand you order...");
        printf("\tPlease enter any key to continue...(back to menu)");
        getchar();
        rewind(stdin);
        Savegood(head);
    }
    Emptythelist(head);

    return 0;
}