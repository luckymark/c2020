#ifndef SKIPLIST_SKIPLIST_H
#define SKIPLIST_SKIPLIST_H

#define MAX_LEVEL 3

/*********************************************************************************
  For convenience, it is assumed that every value is greater than zero and unique.
 *********************************************************************************/
typedef struct node {
    unsigned int value;
    unsigned int level; // between 0 and MAX_LEVEL
    struct node *forward[MAX_LEVEL + 1];
} Node;

int randomLevel();
Node *createList();
void printList(Node *head);
void destroyList(Node *head);
Node *searchNode(Node *head, unsigned int value);
int insertNode(Node *head, unsigned int value);
int removeNode(Node *head, unsigned int value);

#endif //SKIPLIST_SKIPLIST_H
