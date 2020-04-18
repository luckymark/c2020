//
// Created by 20694 on 2020/4/16.
//

#ifndef UNTITLED1_WAREHOUSE_H
#define UNTITLED1_WAREHOUSE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"
#define T 1
typedef struct Store{
    char model[30];
    int num;
    struct Store*next;
}store;
store* read(store*head);
void write(store*head);
store* choose(int cho,store*head);
store* Deletenode(store*head,int y);
void Displaynode(store *head);
store*appendnode(store*head);
#endif //UNTITLED1_WAREHOUSE_H
