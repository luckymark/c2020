//
// Created by surfaceCS on 2020/3/8.
//

#include<stdio.h>
#include<stdlib.h>
#include"Linkedlist.h"

void Inputvalue(Link* head)
{
    printf("Input the 10 values of the link:");
    Link* current = head;
    int n;
    for (int i = 1; i <= Length; i++)
    {
        if (scanf("%d", &n) == 1)
        {
            current->value = n;
            current = current->next;
        }
        else
        {
            printf("Input error");
            exit(EXIT_FAILURE);
        }
    }
}

void Showvalue(Link* head)
{
    Link* prev=head;
    while (prev != NULL)
    {
        printf("%d\n", prev->value);
        prev = prev->next;
    }
}

void Emptythelist(Link* head)
{
    Link* prev=head,*current;
    while (prev != NULL)
    {
        current = prev;
        prev = prev->next;
        free(current);
    }
}

Link* Reverselink(Link* head)
{
    Link* temp = head;
    Link* temp2;
    while (temp->next != NULL)
    {
        temp2 = temp->next;
        temp->next = temp2->next;
        temp2->next = head;
        head = temp2;
    }
    return head;
}

int Findfirst5link(Link* head)
{
    int n=1;
    while (head != NULL)
    {
        if (head->value == 5)
            return n;
        n++;
        head = head->next;
    }
    return -1;
}

int Findnext5link(Link* head)
{
    int n = 1;
    int flag = 0;
    while (head != NULL)
    {
        if (head->value == 5)
            flag++;
        if (flag == 2)
            return n;
        n++;
        head = head->next;
    }
    return -1;
}