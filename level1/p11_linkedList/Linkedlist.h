//
// Created by surfaceCS on 2020/3/8.
//

#ifndef P11_LINKEDLIST_LINKEDLIST_H
#define P11_LINKEDLIST_LINKEDLIST_H
typedef int Item;

#define Length 10

typedef struct link {
    Item value;
    struct link* next;
}Link;


void Inputvalue(Link* head);         //遍历链表，依次赋值。

Link* Reverselink(Link* head);        //反转链表。

int Findfirst5link(Link* head);      //找到链表中第一个为5的节点序号。

int Findnext5link(Link* head);       //找到链表中第二个为5的节点序号。

void Showvalue(Link* head);          //输出链表每个节点的值。

void Emptythelist(Link* head);       //free链表的每个节点。
#endif //P11_LINKEDLIST_LINKEDLIST_H
