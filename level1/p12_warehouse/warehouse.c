#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAXN 25  //名字的最大长度
struct Good {
    char name[MAXN];
    int number;
    struct Good* next;
};

struct Good* head;  //有空头链表
char filePath[100] = "./warehouse.txt";

struct Good* newNode();            //创造新节点
void showHelp();                   //打印帮助
void showList();                   //显示列表
int addGood(char* name, int num);  //增减货物
void readList();                   //打开时读入文件
void writeList();                  //退出时输出到文件
void delLink();                    //删除链表

int main() {
    head = newNode();
    readList();
    while (1) {
        int number = 0;
        char name[MAXN];
        int num;
        showHelp();
        scanf("%d", &num);
        switch (num) {
            case 0:
                showList();
                break;
            case 1:
            case 2:
                system("cls");
                printf("please input the good`s name\n");
                scanf("%s", name);
                printf("please input the number:\n");
                scanf("%d", &number);
                break;
            case 3:
                writeList();
                break;
            default:
                continue;
        }
        if (num == 3) {
            break;
        }
        if (num == 1) {
            addGood(name, number);
        } else if (num == 2) {
            addGood(name, -number);
        }
    }
    delLink();
}

struct Good* newNode() {
    struct Good* good = (struct Good*)malloc(sizeof(struct Good));
    strcpy(good->name, "");
    good->number = 0;
    good->next = NULL;
    return good;
}

void showHelp() {
    system("cls");
    printf("Opinion\n");
    printf("0 -- Show inventory list\n");
    printf("1 -- Warehouse\n");
    printf("2 -- Outbound\n");
    printf("3 -- Exit\n");
}

void showList() {
    //    system("cls");
    struct Good* u = head->next;
    if (u == NULL) {
        printf("Nothing here.\n");
    }
    while (u != NULL) {
        printf("%-*s -- %4d\n", MAXN, u->name, u->number);
        u = u->next;
    }
    system("pause");
}

int addGood(char* name, int num) {
    struct Good* u = head->next;
    struct Good* v = head;  // v是u的上一个，用于删除
    while (u != NULL) {
        if (strcmp(u->name, name) == 0) {
            break;
        }
        v = u;
        u = u->next;
    }
    if (u == NULL) {
        u = newNode();
        strcpy(u->name, name);
        v->next = u;
    }

    //错误行为
    if (u->number + num < 0) {
        printf("Wrong!\n");
        system("pause");
        return 0;
    } else {
        u->number += num;
    }

    //删除
    if (u->number == 0) {
        v->next = u->next;
        free(u);
    }
    return 1;
}

void readList() {
    char name[25];
    char temp[5];
    int number;
    FILE* file = fopen(filePath, "r");
    while (fscanf(file, "%s%s%d", name, temp, &number) == 3) {
        addGood(name, number);
    }
    fclose(file);
}

void writeList() {
    FILE* file = fopen(filePath, "w");
    for (struct Good* u = head->next; u != NULL; u = u->next) {
        fprintf(file, "%-*s -- %3d\n", MAXN, u->name, u->number);
    }
    fclose(file);
}

void delLink() {
    struct Good* u = head;
    struct Good* v = head->next;
    while (u != NULL) {
        free(u);
        u = v;
        if (v != NULL) v = v->next;
    }
    head = NULL;
}
