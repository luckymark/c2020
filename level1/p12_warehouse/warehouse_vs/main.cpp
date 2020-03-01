#include <stdio.h>
#include "goods.h"
int main() 
{
    // read from file
    heap heap1;
    init_heap_file(&heap1);
    // menu
    int choice = -1;
    while (choice)
    {
        printf("1: show the list;\n");
        printf("2: put goods in the storage;\n");
        printf("3: get goods from the storage;\n");
        printf("0: end of the program and save the data;\n");
        printf("Please input your choice: ");
        scanf_s("%d", &choice);
        switch (choice)
        {
        case 1: print_goods_list(&heap1); break;
        case 2: in_goods(&heap1); break;
        case 3: out_goods(&heap1); break;
        case 0:
            storage_heap_file(&heap1); break;
        default:break;
        }
        printf(" -*-*-*-*-*-*-*-*-*-*-*-*-*-\n\n");
    }
    return 0;
}
