#include <stdio.h>
#include "goods.h"

int main(void) {
    Goods *goods = init();

    printf("Welcome to Inventory Management System!\n\n");

    while (1) {
        int num;
        size_t status = 0;

        printf("1) Show inventory list\n");
        printf("2) Warehouse\n");
        printf("3) Outbound\n");
        printf("0) Save and quit\n");
        printf("Enter the number to perform the corresponding operation: ");
        scanf("%d", &num);

        if (num < 0 || num > 3) {
            printf("\nNumbering error!\n\n");
            continue;
        } else {
            switch (num) {
                case 1:
                    show_list(goods);
                    break;

                case 2:
                    warehouse(goods);
                    break;

                case 3:
                    outbound(goods);
                    break;

                case 0:
                    status = save(goods);
                    if (status == 0) {
                        printf("\nSave failed!\n\n");
                        printf("Whether to force quit(0:Yes(default) Others:No): ");
                        scanf("%d", &num);
                        if (num == 0) {
                            status = -1;
                        }
                    } else {
                        printf("\nSaved successfully!\n\n");
                    }
                    break;

                default:
                    break;
            }
        }

        if (status != 0) {
            break;
        }
    }

    printf("Bye!\n");

    return 0;
}
