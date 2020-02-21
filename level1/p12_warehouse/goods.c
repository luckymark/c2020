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

    printf("\n执行入库操作...\n\n");
    printf("请输入入库的商品型号(001~004 或 输入 0 以退出): ");
    scanf("%d", &model);

    if (model != 0) {
        if (model > 4 || model < 1) {
            printf("\n该商品不存在！\n\n");
        } else {
            printf("请输入入库数量: ");
            scanf("%d", &quantity);

            if (quantity <= 0) {
                printf("\n数量必须为正整数！\n\n");
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

                printf("\n入库成功！\n\n");
            }
        }
    }
}

void outbound(Goods *goods) {
    int model, quantity;

    printf("\n执行出库操作...\n\n");
    printf("请输入出库的商品型号(001~004 或 输入 0 以退出): ");
    scanf("%d", &model);

    if (model != 0) {
        if (model > 4 || model < 1) {
            printf("\n该商品不存在！\n\n");
        } else {
            printf("请输入出库数量: ");
            scanf("%d", &quantity);

            if (quantity <= 0) {
                printf("\n数量必须为正整数！\n\n");
            } else {
                switch (model) {
                    case 1:
                        if (goods->g1 < quantity) {
                            printf("\n库存不足！\n\n");
                        } else {
                            goods->g1 -= quantity;
                            printf("\n出库成功！\n\n");
                        }
                        break;

                    case 2:
                        if (goods->g2 < quantity) {
                            printf("\n库存不足！\n\n");
                        } else {
                            goods->g2 -= quantity;
                            printf("\n出库成功！\n\n");
                        }
                        break;

                    case 3:
                        if (goods->g3 < quantity) {
                            printf("\n库存不足！\n\n");
                        } else {
                            goods->g3 -= quantity;
                            printf("\n出库成功！\n\n");
                        }
                        break;

                    case 4:
                        if (goods->g4 < quantity) {
                            printf("\n库存不足！\n\n");
                        } else {
                            goods->g4 -= quantity;
                            printf("\n出库成功！\n\n");
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