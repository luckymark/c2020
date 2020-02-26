#include <stdio.h>
#include <stdlib.h>
#include "goods.h"

Goods* init() {
    Goods *goods = (Goods*)malloc(sizeof(Goods));
    FILE *fp = fopen("goods.dat", "rb");

    if (fp == NULL) {
        goods->g1 = 0;
        goods->g2 = 0;
        goods->g3 = 0;
        goods->g4 = 0;
    } else {
        fread(goods, sizeof(Goods), 1, fp);
    }

    return goods;
}

void show_list(Goods *goods) {
    printf("\n型号\t数量\n");
    printf("001\t%d\n", goods->g1);
    printf("002\t%d\n", goods->g2);
    printf("003\t%d\n", goods->g3);
    printf("004\t%d\n\n", goods->g4);
}

void warehouse(Goods *goods) {
    int model, quantity;

    printf("\nPerforming warehousing operations...\n\n");
    printf("Please enter the product model(001~004 or enter 0 to quit): ");
    scanf("%d", &model);

    if (model != 0) {
        if (model > 4 || model < 1) {
            printf("\nThis product does not exist!\n\n");
        } else {
            printf("Please enter the quantity: ");
            scanf("%d", &quantity);

            if (quantity <= 0) {
                printf("\nQuantity must be a positive integer!\n\n");
            } else {
                switch (model) {
                    case 1:
                        goods->g1 += quantity;
                        break;

                    case 2:
                        goods->g2 += quantity;
                        break;

                    case 3:
                        goods->g3 += quantity;
                        break;

                    case 4:
                        goods->g4 += quantity;
                        break;

                    default:
                        break;
                }

                printf("\nSuccess!\n\n");
            }
        }
    }
}

void outbound(Goods *goods) {
    int model, quantity;

    printf("\nPerform outbound operations...\n\n");
    printf("Please enter the product model(001~004 or enter 0 to quit): ");
    scanf("%d", &model);

    if (model != 0) {
        if (model > 4 || model < 1) {
            printf("\nThis product does not exist!\n\n");
        } else {
            printf("Please enter the quantity: ");
            scanf("%d", &quantity);

            if (quantity <= 0) {
                printf("\nQuantity must be a positive integer!\n\n");
            } else {
                switch (model) {
                    case 1:
                        if (goods->g1 < quantity) {
                            printf("\nInsufficient inventory!\n\n");
                        } else {
                            goods->g1 -= quantity;
                            printf("\nSuccess!\n\n");
                        }
                        break;

                    case 2:
                        if (goods->g2 < quantity) {
                            printf("\nInsufficient inventory!\n\n");
                        } else {
                            goods->g2 -= quantity;
                            printf("\nSuccess!\n\n");
                        }
                        break;

                    case 3:
                        if (goods->g3 < quantity) {
                            printf("\nInsufficient inventory!\n\n");
                        } else {
                            goods->g3 -= quantity;
                            printf("\nSuccess!\n\n");
                        }
                        break;

                    case 4:
                        if (goods->g4 < quantity) {
                            printf("\nInsufficient inventory!\n\n");
                        } else {
                            goods->g4 -= quantity;
                            printf("\nSuccess!\n\n");
                        }
                        break;

                    default:
                        break;
                }
            }
        }
    }
}

size_t save(Goods *goods) {
    FILE *fp = fopen("goods.dat", "wb");
    size_t status = 0;

    status = fwrite(goods, sizeof(Goods), 1, fp);
    fclose(fp);

    return status;
}