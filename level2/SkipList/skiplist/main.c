#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAX_L 4
typedef struct __KL__ {
    int a;
    int level;
    struct __KL__* next[MAX_L + 1]; // next[MAX_L] 指向前面一个节点，其余都是向后指
}kl;
void init_kl(kl* pkl, int num);
kl* find_value(kl* head, int num);
void insert(kl* head, int num);
void del_all(kl* head);


int main()
{
    srand(time(NULL));
    kl* head = (kl*)malloc(sizeof(kl));
    init_kl(head,0);
    head->level = MAX_L - 1;
    for(int i = 1; i <= 88; i++) {
        insert(head,i);
    }
    kl* find = find_value(head,55);
    printf("%d %d %d", find->a,find->next[0]->a,find->next[MAX_L]->a);
    del_all(head);
    return 0;
}



void init_kl(kl* pkl, int num)
{
    pkl->a = num;
    pkl->level = rand() % MAX_L;
    for(int i = 0; i < MAX_L + 1; i++) {
        pkl->next[i] = NULL;
    }
}
kl* find_value(kl* head, int num)
{
    kl* cur = head;
    kl* cur_last = head;
    int level = MAX_L - 1;
    bool pd = false;
    while(level != -1) {
        if(cur->a < num) {
            cur_last = cur;
            cur = cur->next[level];
            while(cur == NULL && level != -1) {
                level -= 1;
                if(level != -1) {
                    cur = cur_last->next[level];
                }
            }
        }
        else if(cur->a > num) {
            level -= 1;
            if(level > -1) {
                cur = cur_last->next[level];
            }
        }
        else {
            pd = true;
            break;
        }
    }
    if(pd) {
        return cur;
    } else {
        printf("%d is not in the list.",num);
        return NULL;
    }
}
void insert(kl* head, int num)
{
    kl* cur = head;
    kl* cur_last = head;
    int level = MAX_L - 1;
    bool pd = false;
    while(level != -1) {
        if(cur->a < num) {
            cur_last = cur;
            cur = cur->next[level];
            while(cur == NULL && level != -1) {
                level -= 1;
                if(level != -1) {
                    cur = cur_last->next[level];
                }
            }
        }
        else if(cur->a > num) {
            level -= 1;
            if(level > -1) {
                cur = cur_last->next[level];
            }
        }
        else {
            pd = true;
            break;
        }
    }
    if(pd) {
        printf("%d is already in the list.", num);
    }
    else {
        kl* in_kl = (kl*)malloc(sizeof(kl));
        init_kl(in_kl,num);
        kl* dump;
        if(in_kl->level <= cur_last->level) {
            for(int i = 0; i <= in_kl->level; i++) {
                dump = cur_last->next[i];
                cur_last->next[i] = in_kl;
                in_kl->next[i] = dump;
            }
            in_kl->next[MAX_L] = cur_last;
            cur = in_kl->next[0];
            if(cur != NULL) {
                cur->next[MAX_L] = in_kl;
            }
        }
        else {
            for(int i = 0; i <= cur_last->level; i++) {
                dump = cur_last->next[i];
                cur_last->next[i] = in_kl;
                in_kl->next[i] = dump;
            }
            in_kl->next[MAX_L] = cur_last;
            cur = in_kl->next[0];
            if(cur != NULL) {
                cur->next[MAX_L] = in_kl;
            }
            cur = cur_last;
            int need_level = cur->level + 1;
            while(need_level != MAX_L) {
                cur = cur->next[MAX_L];
                if(cur->level >= need_level) {
                    for(int i = need_level; i <= cur->level; i++) {
                        dump = cur->next[i];
                        cur->next[i] = in_kl;
                        in_kl->next[i] = dump;
                    }
                    need_level = cur->level + 1;
                }
            }
        }
    }
}
void del_all(kl* head)
{
    kl* cur = head;
    while(cur != NULL) {
        cur = cur->next[0];
        free(head);
        head = cur;
    }
}