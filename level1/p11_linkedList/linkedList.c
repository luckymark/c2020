#include <stdio.h>
#include <stdlib.h>
struct Node {
    int value;
    struct Node* next;
};

//分配新节点
struct Node* newNode(int value) {
    struct Node* node = malloc(sizeof(struct Node));
    node->value = value;
    node->next = NULL;
    return node;
}

//打印链表
void printLink(struct Node* head) {
    while(1) {
        printf("%d,", head->value);
        if(head->next == NULL){
            break;
        }else {
            head = head->next;
        }
    }
    printf("\n");
}

//反序链表，返回原来的尾节点（新的头节点）
struct Node* reverseLink(struct Node* head) {
    struct Node* lNode = head;
    struct Node* node  = head->next;
    struct Node* rNode = head->next->next;
    if(node == NULL) {  //只有一个节点
        return head;
    }else{
        lNode->next = NULL;
    }

    while(1){
        node->next = lNode;
        if(rNode == NULL){
            break;
        }
        lNode = node;
        node = rNode;
        rNode = rNode->next;
    }
    return node;
}

//删除链表
void delLink(struct Node* head) {
    while(head != NULL) {
        struct Node *p = head;
        head = head->next;
        free(p);
    }
}

//查找num在链表第times出现的位置,失败返回-1
int findLink(struct Node* head, int num,int times){
    int p = -1;
    while(times){
        if(head == NULL) {
            return -1;
        }
        if(head->value == num){
            times--;
        }
        head = head->next;
        p++;
    }
    printf("On the %dth\n",p+1);
    return p;
}

int main() {
    struct Node* head = newNode(0); //无空头链表
    struct Node* p = head;
    for (int i = 1; i <= 10; ++i) {
        p->next = newNode(i);
        p = p->next;
    }
    for (int i = 1; i < 7; ++i) {
        p->next = newNode(i);
        p = p->next;
    }
    printLink(head);
    findLink(head,5,1);
    findLink(head,5,2);
    head = reverseLink(head);
    printLink(head);
    findLink(head,5,1);
    findLink(head,5,2);
    delLink(head);
    return 0;
}
