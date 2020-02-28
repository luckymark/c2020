//
// Created by asus on 2020/2/28.
//

#ifndef LIST_BASE_H
#define LIST_BASE_H

// base definitions
#define FIND_VALUE 5
#define INPUT_STOP -1
#define FIND_END_RETURN -1

// base structures
typedef struct __node__{
    int value;
    struct __node__* next;
} node;

typedef struct __list__{
    node* head;
    node* find;
    node* last;
    int count;
} _list;

// base functions
void init_list(_list* list);
void input_list(_list* list);
void output_list(_list list);
void del_list(_list* list);
int find_node(_list* list, int node_value);
void find_all(_list* list, int node_value);
void reverse_list(_list* list);

#endif //LIST_BASE_H
