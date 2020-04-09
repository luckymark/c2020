#include <stdio.h>
#include <stdlib.h>

// node结构类型的声明  以及定义这种结构为Node 这种结构指针为NodeP
typedef struct node {
    int date;
    struct node *next;
} Node, *NodeP;

NodeP getNewNode();
void insertNode(NodeP linklist, int n, NodeP address);
void serchN(NodeP linklist, int n);
NodeP converseLL(NodeP linklist);
void printLL(NodeP linklist);
NodeP getNewNode2();
NodeP getNewNode();
NodeP getLinklist(int lenth);

//链表生成及初始化
NodeP getLinklist(int lenth) {
    NodeP headP, nodeP, endP;
    headP = nodeP = endP = (Node *)malloc(sizeof(Node));

    for (int i = 1; i <= lenth; i++) {
        endP = (Node *)malloc(sizeof(Node));
        printf("Plese input the node's data of number %d :\n", i);
        scanf("%d", &endP->date);

        nodeP->next = endP;
        nodeP = endP;
    }
    endP->next = NULL;
    return headP;
}

//在第n+1个位置插入一个地址为address的结点
void insertNode(NodeP linklist, int n, NodeP address) {
    int i = 0;
    NodeP newNodeP, curseP = linklist;

    //先尝试把光标移动到第n个结点去
    while (i < n && curseP->next != NULL) {
        curseP = curseP->next;
        i++;
    }

    if (i == n) {
        newNodeP = address;
        newNodeP->next = curseP->next;
        curseP->next = newNodeP;
    } else {
        printf("ERROR:the number %d code isn't exsit\n", n);
    }
}

//创建一个新的结点并初始化  最后返回结点地址
NodeP getNewNode() {
    NodeP newnode = (Node *)malloc(sizeof(Node));
    printf("Plese input this new node's data:\n");
    scanf("%d", &newnode->date);
    newnode->next = NULL;
    return newnode;
}
//创建一个新的结点但不初始化  最后返回结点地址
NodeP getNewNode2() {
    NodeP newnode = (Node *)malloc(sizeof(Node));
    newnode->next = NULL;
    return newnode;
}

//遍历输出链表数据
void printLL(NodeP linklist) {
    //用一个！= null 就不用再额外加个lenth变量来确定循环上限了
    //移动指针到下一个结点 要放在printf前 是为了不输出head结点的数据
    while (linklist->next != NULL) {
        linklist = linklist->next;  //移动指针
        printf("%d ", linklist->date);
    }
    putchar('\n');
}

//获得一个链表的反序链表
NodeP converseLL(NodeP linklist) {
    NodeP newLL = getLinklist(0);  //生成一个长度为0的链表 即只有head
    NodeP newNode;
    while (linklist->next != NULL) {
        linklist = linklist->next;
        newNode = getNewNode2();
        newNode->date = linklist->date;
        insertNode(newLL, 0, newNode);
    }
    return newLL;
}

//查找链表中所有的n 并且输出每个n的位置
void serchN(NodeP linklist, int n) {
    int num=0;
    for (int i = 1; linklist->next != NULL; i++) {
        linklist = linklist->next;
        if (linklist->date == n) {
            printf("Nth node's data = %d (N=%d)\n", n, i);
            num++;
        }
    }
    printf("yi gong you N ge %d (N=%d)\n", n, num);
}

int main(void) {
    int lenth;
    puts("Please input the lenth of Linklist:");
    scanf("%d", &lenth);

    NodeP linklist1 = getLinklist(lenth);  //生成一个链表并初始化
    printLL(linklist1);                    //打印一次
    serchN(linklist1, 5); //查找链表中所有的5 
    linklist1 = converseLL(linklist1);     //将linklist1反序
    printLL(linklist1);                    //打印一次
    serchN(linklist1, 5); //查找链表中所有的5 

    return 0;
}
