//for maze generate
#ifndef LIST_H
#define LIST_H

#include<stdio.h>
#include<stdlib.h>
struct node{
    int x;
    int y;
    //position
    struct node* next;
    //std linked list
};
extern struct node *head;
//head ptr
extern int listSize;

void insertList(int x,int y);
void delList(int pos);
void showList();
struct node *getElement(int index);
static inline int getListSize(){ 
    return listSize;
}

#endif
