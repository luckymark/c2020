#include <stdio.h>
#include "SkipList.h"

int main(void) {
    Node *head = createList();

    insertNode(head, 5);
    insertNode(head, 6);
    insertNode(head, 3);
    insertNode(head, 18);
    insertNode(head, 2);
    insertNode(head, 3);
    removeNode(head, 6);
    removeNode(head, 16);
    insertNode(head, 115);
    insertNode(head, 1234);
    insertNode(head, 567);
    printList(head);
    destroyList(head);

    return 0;
}
