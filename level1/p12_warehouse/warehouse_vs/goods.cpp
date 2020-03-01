//
// Created by asus on 2020/2/29.
//

#include "goods.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static int LEFT(int i)
{
    return i + i + 1;
}
static int RIGHT(int i)
{
    return i + i + 2;
}
static void swap(goods* goods1, goods* goods2)
{
    goods goods3 = *goods1;
    *goods1 = *goods2;
    *goods2 = goods3;
}
void init_heap_file(heap* heap1)
{
    FILE* fp;
    fopen_s(&fp,"goods_list.txt", "r");
    fscanf_s(fp, "%d", &heap1->kinds_num);
    heap1->goods_arr = (goods*)malloc(sizeof(goods) * heap1->kinds_num);
    for (int i = 0; i < heap1->kinds_num; i++) {
        fscanf_s(fp, "%s", heap1->goods_arr[i].name, MAX_TITLE);
        fscanf_s(fp, "%d", &heap1->goods_arr[i].num);
        // toupper
        for (int j = 0; heap1->goods_arr[i].name[j] != '\0' && j < MAX_TITLE; j++) {
            if (heap1->goods_arr[i].name[j] >= 'a' && heap1->goods_arr[i].name[j] <= 'z') {
                heap1->goods_arr[i].name[j] += 'A' - 'a';
            }
        }
    }
    fclose(fp);
    build_max_heap(heap1);
}
void max_heapify(heap* heap1, int i)
{
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest = i;
    if (l < heap1->kinds_num && strcmp(heap1->goods_arr[l].name, heap1->goods_arr[largest].name) > 0)
        largest = l;
    if (r < heap1->kinds_num && strcmp(heap1->goods_arr[r].name, heap1->goods_arr[largest].name) > 0)
        largest = r;
    if (largest != i) {
        swap(&heap1->goods_arr[i], &heap1->goods_arr[largest]);
        max_heapify(heap1, largest);
    }
}
void build_max_heap(heap* heap1)
{
    for (int i = heap1->kinds_num / 2 - 1; i >= 0; i--)
        max_heapify(heap1, i);
}
void print_goods_list(heap* heap1)
{
    heap heap_copy;
    heap_copy.kinds_num = heap1->kinds_num;
    heap_copy.goods_arr = (goods*)malloc(sizeof(goods) * heap1->kinds_num);
    memcpy(heap_copy.goods_arr, heap1->goods_arr, sizeof(goods) * heap1->kinds_num);
    for (int i = heap_copy.kinds_num - 1; i >= 1; i--) {
        swap(&heap_copy.goods_arr[0], &heap_copy.goods_arr[i]);
        heap_copy.kinds_num--;
        max_heapify(&heap_copy, 0);
    }
    printf("The goods list:(name) : (number)\n");
    for (int i = 0; i < heap1->kinds_num; i++)
        printf("%s : %d\n", heap_copy.goods_arr[i].name, heap_copy.goods_arr[i].num);
}
void in_goods(heap* heap1)
{
    goods goods_in = { '\0' };
    printf("Please input the goods' name:\n");
    scanf_s("%s", goods_in.name, MAX_TITLE);
    // toupper
    for (int i = 0; i < MAX_TITLE && goods_in.name[i] != '\0'; i++) {
        if (goods_in.name[i] >= 'a' && goods_in.name[i] <= 'z')
            goods_in.name[i] += 'A' - 'a';
    }
    printf("Please input the goods' number which you want to put into storage:\n");
    scanf_s("%d", &goods_in.num);
    int find_num = 0;
    if ((find_num = find_goods(heap1, goods_in.name)) < heap1->kinds_num) {
        heap1->goods_arr[find_num].num += goods_in.num;
        printf("You have added %d of %s.\n", goods_in.num, goods_in.name);
    }
    else {
        printf("You have added a new kind of goods(%s) in the goods' storage.\n",goods_in.name);
        heap1->kinds_num++;
        goods* goods_new_arr = (goods*)malloc(sizeof(goods) * heap1->kinds_num);
        for (int i = 0; i < heap1->kinds_num - 1; i++) {
            goods_new_arr[i] = heap1->goods_arr[i];
        }
        memcpy(goods_new_arr[heap1->kinds_num - 1].name, goods_in.name, sizeof(char) * MAX_TITLE);
        goods_new_arr[heap1->kinds_num - 1].num = goods_in.num;
        free(heap1->goods_arr);
        heap1->goods_arr = goods_new_arr;
        build_max_heap(heap1);
    }
}
void out_goods(heap* heap1)
{
    goods goods_out = { '\0' };
    printf("Please input the goods' name:\n");
    scanf_s("%s", goods_out.name,40);
    // toupper
    for (int i = 0; i < MAX_TITLE && goods_out.name[i] != '\0'; i++)
        goods_out.name[i] += 'A' - 'a';
    printf("Please input the goods' number which you want to get from storage:\n");
    scanf_s("%d", &goods_out.num);
    int find_num = 0;
    if ((find_num = find_goods(heap1, goods_out.name)) < heap1->kinds_num) {
        if (heap1->goods_arr[find_num].num >= goods_out.num) {
            heap1->goods_arr[find_num].num -= goods_out.num;
            printf("You have get %d of %s from the storage.", goods_out.num, goods_out.name);
            printf("There are(is) %d %s left.", heap1->goods_arr[find_num].num, goods_out.name);
        }
        else {
            printf("%s is only %d left.\n", goods_out.name, heap1->goods_arr[find_num].num);
            printf("Your number is bigger than that.");
        }
    }
    else {
        printf("The name of goods is not in the storage, please check the name.");
    }
}
int find_goods(heap* heap1, char* find_name)
{
    int i = 0;
    for (i = 0; i < heap1->kinds_num; i++) {
        if (strcmp(find_name, heap1->goods_arr[i].name) == 0)
            break;
    }
    return i;
}

void storage_heap_file(heap* heap1)
{
    FILE* fp;
    fopen_s(&fp,"goods_list.txt", "w");
    fprintf(fp, "%d\n", heap1->kinds_num);
    for (int i = 0; i < heap1->kinds_num; i++) {
        fprintf(fp, "%40s ", heap1->goods_arr[i].name);
        fprintf(fp, "%d\n", heap1->goods_arr[i].num);
    }
    free(heap1->goods_arr);
    fclose(fp);
}
