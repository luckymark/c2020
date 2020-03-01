#ifndef P11_LINKEDLIST_LINKEDLIST_H
#define P11_LINKEDLIST_LINKEDLIST_H

typedef struct node {
    int value;
    struct node *next;
} Node;

Node* createList(int n);
void destroyList(Node *head); // 程序结束之前必须执行此函数释放内存
void printList(Node *head);
int changeNodeValue(Node *head, int n, int value);
int deleteNode(Node *head, int n);
int insertNode(Node *head, int n, int value);
int reverseList(Node *head);

#endif //P11_LINKEDLIST_LINKEDLIST_H
