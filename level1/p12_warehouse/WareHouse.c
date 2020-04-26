#include <conio.h>
#include <stdio.h>
#include <windows.h>

//同时define出Item数据类型及这种类型的指针

typedef struct item {
    int id;
    char name[35];
    int amount;

    struct item *next;
} Item, *ItemP;

ItemP getTempWarehouse();
int mainMenu();
void drawWH(ItemP address);
void drawOptions(int menuOption);
void getInput(int *chP, int *menuOption);
void operate(int menuOption, ItemP TempWarehouse);
void newItem(ItemP address);
void numIncrease(ItemP address);
void numReduce(ItemP address);
void quitAndSave(ItemP TempWarehouse);

//-----------------------------------------------------------------第1个c文件
//链表

//生成一个运行时库存(随开随生,随关随灭)
//数据从data.txt中读取

ItemP getTempWarehouse() {
    //打开data.txt 如果不存在就新建  所以a+
    FILE *file = fopen("data.txt", "a+");

    ItemP headP, itemP, endP;
    headP = itemP = (ItemP)malloc(sizeof(Item));

    endP = (ItemP)malloc(sizeof(Item));
    while ((fscanf(file, "%04d %34s %d", &endP->id, endP->name,
                   &endP->amount)) != EOF) {
        itemP->next = endP;
        itemP = endP;
        endP = (ItemP)malloc(sizeof(Item));
    }
    itemP->next = NULL;
    fclose(file);
    return headP;
}

//-----------------------------------------------------------------第2个c文件
//仓库主体

enum arrow { UP = 72, DOWN = 80 };  // ASCII编码
enum menuOptions { NEW, ADD, MINUS, QUIT };

//主菜单 由库存显示与选项组成
int mainMenu(ItemP TempWarehouse) {
    int ch = 0;
    int menuOption = 0;
    //每一次while包含：渲染库存 渲染选项 读取输入(此处有一次阻塞)
    //执行用户意愿操作
    do {
        drawWH(TempWarehouse);
        drawOptions(menuOption);
        getInput(&ch, &menuOption);
        system("cls");
    } while (ch != 13);  //按下回车即读取完毕 开始执行
    operate(menuOption, TempWarehouse);
    return menuOption;
}

//渲染库存 draw warehouse
void drawWH(ItemP address) {
    ItemP pointer = address->next;
    printf("ID\tNAME\t\t\t\t\tQUANTITY|\n");
    while (pointer != NULL) {
        printf("%04d \t%-34s \t%d\t|\n", pointer->id, pointer->name,
               pointer->amount);
        pointer = pointer->next;
    }
    printf("--------------------------------------------------------|\n");
}

//渲染选项
void drawOptions(int menuOption) {
    printf("\n");
    if (menuOption == NEW) printf("     ▶");
    printf("\t新的物品\n");

    printf("\n");
    if (menuOption == ADD) printf("     ▶");
    printf("\t物品入库\n");

    printf("\n");
    if (menuOption == MINUS) printf("     ▶");
    printf("\t物品出库\n");

    printf("\n");
    if (menuOption == QUIT) printf("     ▶");
    printf("\t保存数据并退出\n");
}

//读取输入
void getInput(int *chP, int *menuOption) {
    if ((*chP = getch()) == 0xE0) {
        *chP = getch();
        switch (*chP) {
            case UP:
                *menuOption += -1;
                if (*menuOption < NEW) *menuOption = QUIT;
                break;
            case DOWN:
                *menuOption += 1;
                if (*menuOption > QUIT) *menuOption = NEW;
                break;
        }
    };
}

//执行用户意愿操作
//此时直接按照menuOption的值来执行
void operate(int menuOption, ItemP TempWarehouse) {
    switch (menuOption) {
        case NEW:
            newItem(TempWarehouse);
            break;
        case ADD:
            numIncrease(TempWarehouse);
            break;
        case MINUS:
            numReduce(TempWarehouse);
            break;
        case QUIT:
            quitAndSave(TempWarehouse);
            break;
    }
}

//选项1：新建条目
void newItem(ItemP address) {
    drawWH(address);
    ItemP newItem = (ItemP)malloc(sizeof(Item));
    printf("INPUT FORMAT:\"id name amount\"\n");
    scanf("%d %s %d", &newItem->id, newItem->name, &newItem->amount);
    //在链表头部插入新的结点
    newItem->next = address->next;
    address->next = newItem;
    puts("operate successfully!");
    Sleep(1000);
    system("cls");
}

//选项2：入库
void numIncrease(ItemP address) {
    drawWH(address);
    puts("Please input ID of the item that you want to add.");
    int id;
    scanf("%d", &id);
    ItemP pointer = address->next;
    while (pointer != NULL) {
        if (pointer->id == id) {
            int num;
            printf("how many do you want ADD?\n");
            scanf("%d", &num);
            pointer->amount += num;
            break;
        }
        pointer = pointer->next;
    }
    if (pointer == NULL) {
        printf("ERROR:This Id isn't exist!\n");
    } else {
        puts("operate successfully!");
    }
    Sleep(1000);
    system("cls");
}

//选项3：出库
void numReduce(ItemP address) {
    drawWH(address);
    puts("Please input ID of the item that you want to minus.");
    int id;
    scanf("%d", &id);
    ItemP pointer = address->next;
    while (pointer != NULL) {
        if (pointer->id == id) {
            int num;
            printf("how many do you want TAKE-OUT?\n");
            scanf("%d", &num);
            if (pointer->amount < num) {
                puts("ERROR:You don't have enough items!");
                Sleep(1000);
                system("cls");
                return;
            }
            pointer->amount -= num;
            break;
        }
        pointer = pointer->next;
    }
    if (pointer == NULL) {
        printf("ERROR:This Id isn't exist!\n");
    } else {
        puts("operate successfully!");
    }
    Sleep(1000);
    system("cls");
}

//选项4：保存至本地并退出
void quitAndSave(ItemP TempWarehouse) {
    ItemP pointer = TempWarehouse->next;
    FILE *file;
    file = fopen("data.txt", "w");
    while (pointer != NULL) {
        fprintf(file, "%04d %34s %d\n", pointer->id, pointer->name,
                pointer->amount);
        pointer = pointer->next;
    }
    fclose(file);
}

int main() {
    system("chcp 65001");  // utf-8编码
    system("cls");         // utf-8编码
    ItemP TempWarehouse = getTempWarehouse();
    while ((mainMenu(TempWarehouse)) != QUIT)
        ;
    return 0;
}