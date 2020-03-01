//
// Created by asus on 2020/2/29.
//

#ifndef WAREHOUSE_GOODS_H
#define WAREHOUSE_GOODS_H


#define MAX_TITLE 40

typedef struct _goods {
    char name[MAX_TITLE];
    int num;
} goods;
typedef struct _heap_ {
    goods* goods_arr;
    int kinds_num;
} heap;

void init_heap_file(heap* heap1);
void max_heapify(heap* heap1, int i);
void build_max_heap(heap* heap1);
void print_goods_list(heap* heap1);
void in_goods(heap* heap1);
void out_goods(heap* heap1);
int find_goods(heap* heap1, char* find_name);
void storage_heap_file(heap* heap1);


#endif //WAREHOUSE_GOODS_H

