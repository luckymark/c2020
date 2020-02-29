//
// Created by tungsten on 2020/2/28.
//
//概念：
//索引：  level1-n层的链表，具有部分元素
//本表：  level0层的链表，本表具有全部元素
//cursor： 指向当前元素的游标
//head：  cur_head的头
//性质：  如果在高层有索引，低层一定有索引；索引的建立是随机的；索引的效果是在有序化的数据中快速跳转
#ifndef SKIPLIST_LIST_H
#define SKIPLIST_LIST_H

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

bool randomVal();
//随机返回bool值.决定是否建立上一层索引
void init(unsigned);
//随机数种子和head指针初始化

bool findList(int val);
void insertList(int val);
void delList(int val);

struct Node{
    unsigned int val;
    //这里把value限制为unsigned是为了偷懒，把搜索时的path（地址）存在每层的cur_head里面
    struct Node* up;
    struct Node* down;
    //层间双向链表
    struct Node* right;
    //层内单向链表
};
static struct Node* head;

#endif //SKIPLIST_LIST_H
