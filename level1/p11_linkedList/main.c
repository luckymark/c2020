#include <stdio.h>
#include "linkedList.h"

int main(void) {
    int n;
    scanf("%d", &n); // 读入链表长度
    Node *head = createList(n); // 创建链表并读入各节点值

    printList(head);
    reverseList(head);
    printList(head);

    // find 5
    Node *node = head->next;
    int i = 1;
    while (node) {
        if (node->value == 5) {
            printf("%d\n", i);
        }
        node = node->next;
        i++;
    }
    printf("-1\n");

    destroyList(head); // malloc 的内存必须释放

    return 0;
}
