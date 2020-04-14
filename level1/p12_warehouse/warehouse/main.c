#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getch.h"

typedef struct _goods {
    char* name;
    int number;
} Goods;  //货物结构

typedef struct _node {
    Goods goods;
    struct _node* next;
} Node;  //链表

typedef struct _list{
    Node* head;
    Node* tail;
} List;

void add(List* pList,Goods goods);
void start();
void print(List* pList);
void push(List* pList,char* s,int n);//入库
void pop(List* pList,char* s,int n);//出库

int main() {
    start();
    int number;
    char s[100];
    List list;
    list.head = NULL;
    list.tail = NULL;
    FILE*fp = fopen("warehouse.txt","r+");
    while(1) {
        if( fscanf(fp, "%s %d",s, &number) == 2) {
            Goods goods;
            goods.number = number;
            goods.name = strdup(s);
            add(&list, goods);
        }
        else {break;}
    }
    fclose(fp);//把文件中的货物信息加载到链表中
    int c;
    do {
        c = (int)getch();
        switch (c) {
        case 49:{print(&list);}break;
        case 50:{
            printf("请以'名称 数量'的格式输入\n");
            scanf("%s %d",s,&number);
            push(&list,s,number);
            start();
            printf("%s入库%d件\n",s,number);
        }
        break;
        case 51:{
            printf("请以'名称 数量'的格式输入\n");
            scanf("%s %d",s,&number);
            pop(&list,s,number);
            start();
            printf("%s出库%d件\n",s,number);
        }
        break;
        case 52:{
            FILE*fp = fopen("warehouse.txt","w+");
            Node* p;
            for (p=list.head; p; p= p->next) {
                fprintf(fp, "%s %d\n", p->goods.name, p->goods.number);
            }
            fclose(fp);//把链表的信息记录到文件中
        }
        break;
    }
    } while ( c != 52 );
    return 0;
}
void start(){
    system("clear");
    printf("1.显示存货列表\n"
           "2.入库\n"
           "3.出库\n"
           "4.退出程序\n"
           "请按数字键选择操作\n");
}

void print(List* pList) {
    Node *p;
    Node* q;
    for( p= pList->head, q= NULL; p; q= p, p= p->next ) {
        if( p->goods.number == 0) {
            if( q ) {
                q->next = p->next;
            }else {
                pList->head = p->next;
            }
            free(p);
            break;
        }
    }   //删除节点,在显示之前除掉剩余0的货物
    system("clear");
    start();
    p = pList->head;
    for (p; p; p= p->next) {
        printf("%s 剩余 %d件\n", p->goods.name, p->goods.number);
    }
}
void push(List* pList,char* s,int n) {
    Node *p = pList->head;
    if( p==NULL){
        Goods goods;
        goods.name = strdup(s);
        goods.number = n;
        add(pList,goods);   //仓库一无所有时创建第一个节点
    } else {
        for (p; p; p = p->next) {
            if (!strcmp(p->goods.name, s)) {
                p->goods.number += n;
                break;
            }  //找到的话+n个
            else if (p->next == NULL) {
                Goods goods;
                goods.name = strdup(s);
                goods.number = n;
                add(pList, goods);
                break;
            }  //没有的话创建一个
        }
    }
}
void pop(List* pList,char* s,int n) {
    Node *p = pList->head;
    for (p; p; p= p->next) {
        if(!strcmp(p->goods.name,s)) {
            p->goods.number -= n;
            break;
        }
    }
}

void add(List* pList,Goods goods){
    Node *p=(Node*)malloc(sizeof(Node));
    p->goods = goods;
    p->next = NULL;
    if( pList->head) {
        pList->tail->next = p;
        pList->tail = p;
    } else {
        pList->head = p;
        pList->tail = p; //空链表创建第一个节点
    }
}    //创建货物节点