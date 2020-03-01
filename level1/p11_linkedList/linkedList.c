#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

Node* createList(int n) {
    Node *head, *node, *end;

    head = (Node*)malloc(sizeof(Node)); // 头节点无 value 指向第一个节点
    end = head;

    for (int i = 0; i < n; i++) {
        node = (Node*)malloc(sizeof(Node));
        scanf("%d", &node->value);
        end->next = node;
        end = node;
    }

    end->next = NULL;
    return head;
}

void destroyList(Node *head) {
    Node *node = head;

    while (node) {
        head = node->next;
        free(node);
        node = head;
    }
}

void printList(Node *head) {
    Node *node = head->next;

    while (node) {
        printf("%d ", node->value);
        node = node->next;
    }
    printf("\n");
}

int changeNodeValue(Node *head, int n, int value) {
    Node *node = head;

    for (int i = 0; i < n && node; i++) {
        node = node->next;
    }

    if (node) {
        node->value = value;
        return 1;
    } else {
        return 0;
    }
}

int deleteNode(Node *head, int n) {
    Node *node = head;

    for (int i = 0; i < n - 1 && node; i++) {
        node = node->next;
    }

    if (node) {
        Node *del_node = node->next;
        node->next = del_node->next;
        free(del_node);
        return 1;
    } else {
        return 0;
    }
}

int insertNode(Node *head, int n, int value) {
    Node *node = head;

    for (int i = 0; i < n && node; i++) {
        node = node->next;
    }

    if (node) {
        Node *ins_node = (Node*)malloc(sizeof(Node));
        ins_node->value = value;
        ins_node->next = node->next->next;
        node->next = ins_node;
        return 1;
    } else {
        return 0;
    }
}

int reverseList(Node *head) {
    if (head->next) {
        Node *prev = head->next;
        Node *cur = head->next->next;
        Node *temp;

        while (cur) {
            temp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = temp;
        }

        head->next->next = NULL;
        head->next = prev;
        return 1;
    } else {
        return 0;
    }
}
