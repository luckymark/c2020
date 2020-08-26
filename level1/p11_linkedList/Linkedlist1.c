//
// Created by surfaceCS on 2020/3/8.
//

#include<stdio.h>
#include<stdlib.h>
#include"Linkedlist.h"

int main()
{
    Link* head = NULL;
    Link* prev = NULL, * current;
    for (int i = 1; i <= Length; i++)
    {
        current = (Link*)malloc(sizeof(Link));
        if (head == NULL)
            head = current;
        else
            prev->next = current;
        current->next = NULL;
        prev = current;
    }

    Inputvalue(head);

    head=Reverselink(head);

    printf("(The node number starts at 1)\n");

    printf("The first 5 appears at the %dth node\n",Findfirst5link(head));

    printf("The next 5 appears at the %dth node\n",Findnext5link(head));

    Emptythelist(head);

    return 0;
}