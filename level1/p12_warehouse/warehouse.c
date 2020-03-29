#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TYPE_CHAR 13
#define MAX_DATA_AMOUNT 100000
#define DATA_FILENAME "data.txt"

//global
typedef struct Good
{
    char type[MAX_TYPE_CHAR];
    int amount;
} Good;
Good data[MAX_DATA_AMOUNT];
int data_tail = 0;

//prototype
void ShowMenu();
void ShowCurrentList();
int SaveToFile();
void Import();
void Export();
int ReadFromFile();
int IsTypeExists(const Good *pGood);
inline void ShowErrMessage(const char *msg);

int main()
{
    //init
    int index = 0;
    if (0 != ReadFromFile())
    {
        ShowErrMessage("【错误】读取仓库文件失败！");
        exit(1);
    }

    while(index != 4)
    {
        system("cls");
        ShowMenu();
        scanf_s("%d", &index);
        system("cls");
        switch(index)
        {
            case 1:
                ShowCurrentList();
                break;
            case 2:
                Import();
                break;
            case 3:
                Export();
                break;
            case 4:
                if(SaveToFile())
                {
                    ShowErrMessage("【错误】保存仓库文件失败！");
                }
                break;
            default:
                printf("请正确输入序号！ \n");
        }
    }

    return 0;
}

int ReadFromFile()
{
    //init
    FILE *fp = NULL;
    errno_t err;
    err = fopen_s(&fp,DATA_FILENAME,"r");

    //file not exist
    if(2 == err)
    {
        err = fopen_s(&fp,DATA_FILENAME,"w");
        fclose(fp);
        return err;
    }

    //read successfully
    if(0 == err)
    {
        int i;
        for(i = 0;i<MAX_DATA_AMOUNT;i++)
        {
            fscanf_s(fp,"%s\n%d",&data[i].type);
            data_tail++;
            if(feof(fp))
                break;
            fgetc(fp);
        }
        if(data_tail > MAX_DATA_AMOUNT)
            printf("只能显示仓库文件的前 %d 条记录 \n",MAX_DATA_AMOUNT);

        fclose(fp);
    }

    return err;
}

void Export()
{
    //check if data empty
    if(data_tail <= 0)
    {
        ShowErrMessage("仓库是空的");
        return;
    }

    //show message and get input
    Good g;
    printf("请输入货物型号：");
    scanf_s("%s",&g.type,MAX_TYPE_CHAR);
    printf("\n请输入货物数量：");
    scanf_s("%d",&g.amount);

    //check if amount plus
    if(g.amount <= 0)
    {
        ShowErrMessage("请输入正确的货物数量！");
        return;
    }

    //check if type exist
    int index = IsTypeExists(&g);
    if(-1 == index)
    {
        ShowErrMessage("货物型号不存在！");
        return;
    }

    //check if amount exceeded
    if(g.amount > data[index].amount)
    {
        ShowErrMessage("仓库中货物数量不足！");
        return;
    }

    //export
    data[index].amount -= g.amount;

    //delete item if no good left
    if(0 == data[index].amount)
    {
        data[index] = data[data_tail -1];
        data_tail--;
    }
}

void Import()
{
    //check if data full
    if(data_tail >= MAX_DATA_AMOUNT)
    {
        printf("最大记录条数：%d \n",MAX_DATA_AMOUNT);
        ShowErrMessage("【错误】存储的记录条数已达最大值");
        return;
    }

    //show message and get input
    Good g;
    printf("请输入货物型号：");
    scanf_s("%s",&g.type,MAX_TYPE_CHAR);
    printf("\n请输入货物数量：");
    scanf_s("%d",&g.amount);

    //check if amount plus
    if(g.amount <= 0)
    {
        ShowErrMessage("请输入正确的货物数量！");
        return;
    }

    //import
    int index = IsTypeExists(&g);
    if(-1 == index)
    {
        data[data_tail] = g;
        data_tail++;
    }
    else
    {
        data[index].amount += g.amount;
    }

}

inline void ShowErrMessage(const char *const msg)
{
    printf("%s \n",msg);
    system("pause");
}

int IsTypeExists(const Good *const pGood)
{
    int i;
    for(i = 0;i < data_tail;i++)
        if(0 == strcmp(data[i].type,pGood->type))
            return i;

    return -1;
}

int SaveToFile()
{
    //init
    FILE *fp = NULL;
    errno_t err;
    err = fopen_s(&fp,DATA_FILENAME,"w");

    //open successfully
    if(0 == err)
    {
        int i;
        for(i = 0;i<data_tail;i++)
        {
            fprintf_s(fp,"%s\n%d\n",data[i].type,data[i].amount);
        }
        fclose(fp);
    }

    return err;
}

void ShowCurrentList()
{
    int i;
    for(i = 0;i<data_tail;i++)
        printf("第%d条记录\t型号：%s\t数量：%d \n",i,data[i].type,data[i].amount);
}

void ShowMenu()
{
    printf("1.显示存货列表 \n2.入库 \n3.出库 \n4.退出程序 \n");
}
