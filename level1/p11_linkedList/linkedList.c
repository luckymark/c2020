#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int value;
    struct _node* next;
} Node;

typedef struct _list{
    Node* head;
    Node* tail;
} List;

void add(List* pList,int number);
void inverse(List* pList);

int main() {
    List list;
    list.head = NULL;
    list.tail = NULL;
    int number;
    do {
        scanf("%d",&number);
        if ( number != -1) {
            add(&list,number);
        }
    }  while ( number != -1 ); //实现各个节点的value
    inverse(&list);//节点反序
    int cnt = 1;
    Node *p = list.head;
    while( cnt ) {
        if( p ) {
            if (p->value == 5) {
                printf("%d\t", cnt);}//查找value为5的节点
            p = p->next;
            cnt++;
        } else {cnt = 0;
        printf("%d\n",-1);
        }
    }
    return 0;
}

void add(List* pList,int number) {
    Node *p =(Node*)malloc(sizeof(Node));
    p->value = number;
    p->next = NULL;
    if( pList->head) {
        pList->tail->next = p;
        pList->tail = p;
    } else {
        pList->head = p;
        pList->tail = p; //空链表创建第一个节点
    }
}
void inverse(List* pList) {
    if( pList->tail != pList->head) {
        //pList->head->next = NULL;
        Node *p,*q,*r;
        q = pList->head->next;
        for( p= pList->head; r; ) {
            r = q->next;
            q->next = p;
            p = q;
            q = r;
        }//思路混乱的节点反序过程
        pList->head->next = NULL;//处理原来的的head
        p = pList->head;
        pList->head = pList->tail;
        pList->tail = p;  //首尾指针颠倒
    }//首尾指针相等无需操作
}