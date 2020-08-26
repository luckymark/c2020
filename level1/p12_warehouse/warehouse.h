//
// Created by surfaceCS on 2020/3/8.
//

#ifndef P12_WAREHOUSE_WAREHOUSE_H
#define P12_WAREHOUSE_WAREHOUSE_H
#include<stdio.h>

#define LEN 20

int number;

typedef struct good {
    char name[LEN];
    long long number;
    struct good* next;
}Good;

char* s_gets(char* st, int n);                   //引用完美的s_gets函数。

void Menu(void);                                 //展示菜单。

Good* Readgood(Good* head);                      //把文件中的数据读入到链表中。

void Savegood(Good* head);                       //把链表中的数据保存到文件中。

void Showgood(Good* head);                       //展示库存信息。

Good* putin(Good* head);                         //入库信息。

Good* takeout(Good* head);                       //出库信息。

void Emptythelist(Good* head);                   //free链表的每个节点。
#endif //P12_WAREHOUSE_WAREHOUSE_H
