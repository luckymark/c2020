#include <windows.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAXN 4  //链表的最大高度

typedef struct Node {
    int value;
    struct Node* next[MAXN];
} Node;

Node* newHead();                         //生成一个新的头节点
Node* newNode(int value, int high);      //生成一个新的节点
void delList(Node* head);                //以头节点开始删除
void insertNode(int value, Node* head);  //插入一个节点到head的跳表
void delNode(int value, Node* head);     //从head的跳表中删除节点
void printList(Node* head);              //打印链表

int main() {
    srand(time(NULL));
    Node* head = newHead();
    insertNode(10, head);
    insertNode(9, head);
    insertNode(19, head);
    printList(head);
    insertNode(3, head);
    printList(head);
    delNode(9, head);
    printList(head);

    for (int i = 0; i < 20; ++i) {
        insertNode(i, head);
    }
    for (int i = 0; i < 20; i += 2) {
        delNode(i, head);
    }
    printList(head);

    delList(head);
}

Node* newNode(int value, int high) {
    Node* node = malloc(sizeof(Node));
    node->value = value;
    for (int i = 0; i < MAXN; ++i) {
        node->next[i] = NULL;
    }
    return node;
}

Node* newHead() {
    Node* head = newNode(0, MAXN);
    return head;
}

void delList(Node* head) {
    if (head->next[0]) {
        delList(head->next[0]);
    }
    free(head);
}

void insertNode(int value, Node* head) {
    Node* update[MAXN];  //需要修改的节点
    int level = MAXN;
    Node* u = head;
    while (level) {
        Node* v = u->next[level - 1];
        if (v == NULL || v->value > value) {
            update[--level] = u;
        } else {
            u = v;
        }
    }
    int high = 1 + rand() % MAXN;
    Node* node = newNode(value, high);
    for (int i = 0; i < high; ++i) {
        node->next[i] = update[i]->next[i];
        update[i]->next[i] = node;
    }
}

void delNode(int value, Node* head) {
    Node* update[MAXN];
    Node* node = NULL;  //需要删除的节点
    Node* u = head;
    int level = MAXN;
    int flag = 0;  //是否找到节点
    while (level) {
        Node* v = u->next[level - 1];
        if (v == NULL || v->value > value) {
            update[--level] = u;
        } else if (v->value == value) {
            update[--level] = u;
            node = v;
        } else {
            u = v;
        }
    }
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < MAXN; ++i) {
        update[i]->next[i] = node->next[i];
    }
    free(node);
}

void printList(Node* head) {
    Node* u = head;
    while (u->next[0]) {
        u = u->next[0];
        printf("%d,", u->value);
    }
    printf("\n");
}
