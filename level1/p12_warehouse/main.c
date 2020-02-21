#include <stdio.h>
#include "goods.h"

int main(void) {
    Goods *goods = init();

    printf("欢迎使用库存管理系统！\n\n");

    while (1) {
        int num;
        size_t status = 0;

        printf("1) 显示存货列表\n");
        printf("2) 入库\n");
        printf("3) 出库\n");
        printf("0) 保存并退出\n");
        printf("输入编号执行相应操作: ");
        scanf("%d", &num);

        if (num < 0 || num > 3) {
            printf("\n编号错误！\n\n");
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
                        printf("\n保存失败！\n\n");
                        printf("是否强制退出(0:是(默认) 其它:否): ");
                        scanf("%d", &num);
                        if (num == 0) {
                            status = -1;
                        }
                    } else {
                        printf("\n保存成功！\n\n");
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

    printf("再见！\n");

    return 0;
}
