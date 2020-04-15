#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define DEFAULT -1

struct node{
    int value;
    struct  node* next;
};
extern struct node *head;

void makeList();
struct node* findEnd();
void insertList(int target);
void showList();
int findNext(int target,int pos);
void reverseList(struct node *this,struct node *prev);
//recursively reverse
