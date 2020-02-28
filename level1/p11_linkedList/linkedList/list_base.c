//
// Created by asus on 2020/2/28.
//
#include <stdio.h>
#include <stdlib.h>
#include "list_base.h"

void init_list(_list* list)
{
    list->head = NULL;
    list->find = NULL;
    list->last = NULL;
    list->count = 0;
}

void input_list(_list* list)
{
    printf("Please input numbers, %d to stop.\n", INPUT_STOP);
    if(list->head == NULL){
        list->head = (node*) malloc(sizeof(node));
        list->head->next = NULL;
        list->last = list->head;
    }
    scanf("%d",&list->last->value); // more than one input, -1 will be cover
    while(list->last->value != INPUT_STOP) {
        list->last->next = (node*)malloc(sizeof(node));
        list->last = list->last->next;
        list->last->next = NULL;
        scanf("%d",&list->last->value);
    }
}

void output_list(_list list)
{
    printf("Now the number(s) in the list :\n");
    node* cur = list.head;
    while(cur != NULL)
    {
        printf("%d ",cur->value);
        cur = cur->next;
    }
    printf("\n\n");
}

void del_list(_list* list)
{
    list->find = list->head;
    while(list->find != NULL) {
        list->find = list->head->next;
        free(list->head);
        list->head = list->find;
    }
}

int find_node(_list* list, int node_value)
{
    if(list->find == NULL)
        list->find = list->head;
    while(list->find != NULL) {
        list->count++;
        if(list->find->value != node_value)
            list->find = list->find->next;
        else
            break;
    }
    if(list->find == NULL) {
        list->find = list->head;
        list->count = 0;
        return FIND_END_RETURN;
    }
    else{
        list->find = list->find->next;
        return list->count; // do not need to return
    }
}

void find_all(_list* list, int node_value)
{
    printf("The number you want to find is at :\n");
    while(find_node(list, FIND_VALUE) != FIND_END_RETURN)
        printf("%d\n", list->count);

}

void reverse_list(_list* list)
{
    node* head_ori = list->head;
    if(list->head == NULL)
        return;
    else if(list->head->next == NULL)
        goto there; // delete INPUT_STOP(-1) & recreate INPUT_STOP(-1) at the last
    node* cur = list->head->next;
    node* cur_son = NULL;
    while(cur)
    {
        cur_son = cur->next;
        cur->next = list->head;
        list->head = cur;
        cur = cur_son;
    }
    there: // delete INPUT_STOP(-1) & recreate INPUT_STOP(-1) at the last
    list->last = (node*)malloc(sizeof(node));
    head_ori->next = list->last;
    list->last->next = NULL;
    list->last->value = INPUT_STOP;
    cur = list->head;
    list->head = list->head->next;
    free(cur);
}
