#include <stdio.h>
#include <string.h>
#define MAX_NUM 10

//实现如下的菜单（按数字选择菜单功能）：
//显示存货列表
//入库
//出库
//退出程序
//实现菜单对应功能（需记录货物的型号、数量等信息）；
//程序启动时从文件中读取当前库存数据，退出时保存库存数据；
 typedef struct Storages{
    char name[50];
    char type[4];
    int Amount;
    
}store;
void Menu();

void LoadFileInfo(store* MyStores, FILE* myStorage);


int main() {
    int choice;
    FILE* Storage = fopen("myStorage", "ab");
    if (Storage == NULL)
    {
        printf("fail to open this file!");
        return 0;
    }
    store * MyStores;
    while (1){
        Menu();
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                return 0;
                break;
            default:
                printf("请重新输入：\n");
                break;
        }
    }
}

void Menu()
{
printf("Menu:\n");
printf("1.显示存货列表\n");
printf("2.入库\n");
printf("3.出库\n");
printf("4.退出程序\n");
}

void LoadFileInfo(store* MyStores, FILE* myStorage){
    while (myStorage != EOF)
    {

    }
}