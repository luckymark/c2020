#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "SkipList.h"

int randomLevel() {
    return rand() % (MAX_LEVEL + 1);
}

Node *createList() {
    srand(time(NULL));
    Node *head = (Node*)malloc(sizeof(Node));
    head->value = 0;
    head->level = MAX_LEVEL;
    for (int i = 0; i < MAX_LEVEL + 1; i++) {
        head->forward[i] = NULL;
    }
    return head;
}

void printList(Node *head) {
    for (int i = MAX_LEVEL; i >= 0; i--) {
        Node *node = head;
        while (node) {
            if (node->level >= i) {
                printf("%d", node->value);
            }
            printf("\t");
            node = node->forward[0];
        }
        printf("\n");
    }
}

void destroyList(Node *head) {
    Node *node = head->forward[0];
    while (node) {
        free(head);
        head = node;
        node = head->forward[0];
    }
    free(head);
}

Node *searchNode(Node *head, unsigned int value) {
    Node *node = head;
    for (int i = MAX_LEVEL; i >= 0; i--) {
        while (node->forward[i] && node->forward[i]->value < value) {
            node = node->forward[i];
        }
    }
    node = node->forward[0];
    if (node && node->value == value) {
        return node;
    } else {
        return NULL;
    }
}

int insertNode(Node *head, unsigned int value) {
    if (searchNode(head, value)) {
        return 0;
    } else {
        Node *new_node = (Node*)malloc(sizeof(Node));
        new_node->value = value;
        new_node->level = randomLevel();

        Node *node = head;
        for (int i = new_node->level; i >= 0; i--) {
            while (node->forward[i] && node->forward[i]->value < value) {
                node = node->forward[i];
            }
            new_node->forward[i] = node->forward[i];
            node->forward[i] = new_node;
        }

        return 1;
    }
}

int removeNode(Node *head, unsigned int value) {
    Node *remove_node = searchNode(head, value);
    if (remove_node) {
        Node *node = head;
        for (int i = remove_node->level; i >= 0; i--) {
            while (node->forward[i] && node->forward[i]->value < value) {
                node = node->forward[i];
            }
            node->forward[i] = remove_node->forward[i];
        }
        free(remove_node);

        return 1;
    } else {
        return 0;
    }
}
