//
// Created by surfaceCS on 2020/3/8.
//

#include"warehouse.h"
#include<stdlib.h>
#include<Windows.h>
#include<string.h>

char* s_gets(char* st, int n)                         //引用完美的s_gets函数。
{
    char* ret_val;
    char* find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');   // look for newline
        if (find)                  // if the address is not NULL,
            *find = '\0';          // place a null character there
        else
            while (getchar() != '\n')
                continue;          // dispose of rest of line
    }
    return ret_val;
}

void Menu(void)                                  //展示菜单。
{
    system("cls");
    printf("\tThere is %d piece of goods in the warehouse\n\n",number);
    printf("\tSelecting from the following options:\n\n");
    printf("\tA.Show goods\t\tB.Put in goods\n\tC.Take out goods\tQ.quit\n\n");
    printf("\tPlease enter your choice:");
}

Good* Readgood(Good* head)              //把文件中的数据读入到链表中。
{
    number = 0;
    head = NULL;
    Good* current = (Good*)malloc(sizeof(Good)),*prev=NULL;
    FILE* fp;
    fp = fopen("warehouse", "rb");
    while (fread(current, sizeof(Good), 1, fp) == 1)
    {
        if (head == NULL)
            head = current;
        else
            prev->next = current;
        prev = current;
        current = (Good*)malloc(sizeof(Good));
        number++;
    }
    free(current);
    fclose(fp);

    return head;
}

void Savegood(Good* head)              //把链表中的数据保存到文件中。
{
    FILE* fp;
    fp = fopen("warehouse", "wb");
    while (head != NULL)
    {
        fwrite(head, sizeof(Good), 1, fp);
        head = head->next;
    }
    fclose(fp);
}

void Showgood(Good* head)                        //展示库存信息。
{
    system("cls");
    if (head == NULL)
    {
        printf("\tNo goods!\n");
        return;
    }
    printf("\tname\t\t\t\tnumber\n");
    while (head != NULL)
    {
        printf("\t%s\t\t\t\t%d\n", head->name, head->number);
        head = head->next;
    }
}

Good* putin(Good* head)                           //入库信息。
{
    system("cls");
    char ch1[LEN];
    long long n;
    printf("\tPlease enter the name of the goods to put into the warehouse(enter quit to quit):");
    s_gets(ch1, LEN);
    rewind(stdin);
    if (strcmp(ch1, "quit") == 0)
        return head;
    printf("\tPlease enter the name of the number you want to put into the warehouse(enter 0 to quit):");
    scanf("%lld", &n);
    rewind(stdin);
    if (n == 0)
        return head;
    Good* gd = (Good*)malloc(sizeof(Good));
    strcpy(gd->name, ch1);
    gd->number = n;
    gd->next = NULL;
    if (head != NULL)
    {
        Good* pre = head,*current=NULL;
        while (pre != NULL)
        {
            if (strcmp(pre->name, ch1) == 0)
            {
                pre->number += n;
                printf("\tOperate successfully!\n");
                return head;
            }
            current = pre;
            pre = pre->next;
        }
        current->next = gd;
        printf("\tOperate successfully!\n");
        return head;
    }
    else
    {
        head = gd;
        printf("\tOperate successfully!\n");
        return head;
    }
}

Good* takeout(Good* head)                         //出库信息。
{
    system("cls");
    if (head == NULL)
    {
        printf("\tNo goods");
        return head;
    }
    char ch2[LEN];
    long long n;
    printf("\tPlease enter the goods that you want(enter quit to quit):");
    s_gets(ch2, LEN);
    rewind(stdin);
    if (strcmp(ch2, "quit") == 0)
        return head;
    Good* current=NULL,*pre=head;
    while (pre != NULL)
    {
        if (strcmp(pre->name, ch2) == 0)
        {
            printf("\tThere is %d remain...\n", pre->number);
            printf("\tPlease enter the number that you want(enter 0 to quit):");
            scanf("%lld", &n);
            rewind(stdin);
            if (n == 0)
                return head;
            while (pre->number < n)
            {
                printf("\nNot enough,there is only %d remain...", pre->number);
                printf("\tPlease enter the number that you want(enter 0 to quit):");
                scanf("%lld", &n);
                if (n == 0)
                    return head;
                rewind(stdin);
            }
            if (pre->number > n)
            {
                printf("\tOperate successfully!\n");
                pre->number -= n;
                return head;
            }
            if (pre->number == n && current!=NULL)
            {
                current->next = pre->next;
                printf("\tOperate successfully!\n");
                return head;
            }
            if (current == NULL && pre->number==n)
            {
                pre = head;
                head = head->next;
                free(pre);
                printf("\tOperate successfully!\n");
                return head;
            }
        }
        current = pre;
        pre = pre->next;
    }
    printf("\tThere is no goods that you want...\n");
    return head;
}

void Emptythelist(Good* head)
{
    Good* prev = head, * current;
    while (prev != NULL)
    {
        current = prev;
        prev = prev->next;
        free(current);
    }
}