#include <stdio.h>
#include <stdlib.h>
#define MAX_LEVEl 4
#define LEVEL_LENGTH 23

typedef struct skipList {
    int value;//节点的序号
    int content;//节点的内容
    int level;//层级
    struct skipList* plist[MAX_LEVEl];
}SkipList;

int randomLevel(void) {
    int level;
    int RM = rand() % LEVEL_LENGTH;//各层节点的概率
    if (RM >= 7) {
        level = 0;
    }
    else if (RM >= 3) {
        level = 1;
    }
    else if (RM >= 1) {
        level = 2;
    }
    else {
        level = 3;
    }
    return level;
}

SkipList* slCreat(int n) {
    SkipList* head, * node, * end, * NIL;
    head = (SkipList*)malloc(sizeof(SkipList));
    NIL = (SkipList*)malloc(sizeof(SkipList));
    NIL->level = EOF;
    NIL->value = EOF;
    end = head;
    end->value = 0;
    for (int i = 0; i < n; i++) {
        node = (SkipList*)malloc(sizeof(SkipList));
        node->value = rand() % 2 + end->value + 1;//进行测试的初始化的序号，序号是不断随机递增的，这样便于测试删除和插入
        node->level = randomLevel();
        end->plist[0] = node;
        end = node;
    }
    end->plist[0] = NIL;//结束level0的创建
    for (int j = 0; j < MAX_LEVEl - 1; j++) {
        end = head;
        node = head->plist[0];
        while (1) {
            if (node->level >= (j + 1)) {
                end->plist[j + 1] = node;
                end = node;
            }
            node = node->plist[0];
            if (node->plist[0] == NIL) {
                end->plist[j + 1] = NIL;
                break;
            }//各层分别遍历完成初始化
        }
    }
    return head;
}

SkipList* slNTLFind(SkipList* head) {
    while (1) {
        if ((head->level) == EOF) {
            return head;
        }
        head = head->plist[MAX_LEVEl - 1];
    }
}

void MoveValue(SkipList* head, SkipList* NIL) {
    head = head->plist[0];
    while (head!= NIL) {
        head->value = head->value + 1;
        head = head->plist[0];
    }
}

void slInsert(SkipList* head, SkipList* NIL,int number) {
    SkipList* node, * end ,*next;
    end = head;
    node = (SkipList*)malloc(sizeof(SkipList));
    node->level = randomLevel();
    node->value = number;
    for (int i = MAX_LEVEl-1; i >= 0; i--) {
         if (end->plist[i]!=NIL) {
            while (end->plist[i]->value < number) {
                end = end->plist[i];
                if (end->plist[i] == NIL) {
                    break;
                }
            }
            if (node->level >= i) {
                node->plist[i] = end->plist[i];
                end->plist[i] = node;
                if (i == 0) {
                    if ((node->plist[i] != NIL) && (node->value == node->plist[i]->value)) {
                        MoveValue(node, NIL);
                    }
                    break;
                }
            }

        }
        
    }
}

void slDelete(SkipList* head, SkipList* NIL, int number) {
    SkipList* node, * end;
    end = head;
    int success=0;
    for (int i = MAX_LEVEl - 1; i >= 0; i--) {
        if (end->plist[i] != NIL) {
            while (end->plist[i]->value < number) {
                if (end->plist[i] == NIL) {
                    break;
                }
                end = end->plist[i];
            }
                if (end->plist[i]->value == number) {                                                   
                    if (i == 0) {
                        node = end->plist[i];
                        end->plist[i] = end->plist[i]->plist[i];
                        free(node);
                    }
                    else {
                        end->plist[i] = end->plist[i]->plist[i];
                    }
                    success = 1;
                }
                
            }
        }
    if (success==0) {
        printf("没有找到希望删除的节点\n");
    }
    }

void slFree(SkipList* head, SkipList* NIL) {
    SkipList* node,*next;
    node = head;
    while(node!=NIL){              
        next = node->plist[0];        
        free(node);
        node = next;
    }
    free(NIL);
}

int main() {
    SkipList* head, * p, * NIL;
    head = slCreat(80);//初始化一个跳表
    NIL = slNTLFind(head);
    slInsert(head,NIL,55);
    slDelete(head,NIL,55);//正确删除
    slDelete(head, NIL, 555);//错误删除
    p = head;
    while ((p->plist[0]) != NIL) {
        p = p->plist[0];
        printf("%d %d \n", p->value, p->level);//从0遍历
    }
    p = head;
    while ((p->plist[1]) != NIL) {
        p = p->plist[1];
        printf("%d %d \n", p->value, p->level);//从一级节点遍历
    }
    p = head;
    while ((p->plist[2]) != NIL) {
        p = p->plist[2];
        printf("%d %d \n", p->value, p->level);//从二级节点遍历
    }
    slFree(head, NIL);
    return 0;
}
