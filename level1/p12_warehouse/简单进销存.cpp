#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct goods_type
{
    char name[20];
    char xh[20];
    int num;
};
struct goods_type goods[100];
int goods_num=0;

void load_txt()
{
    FILE * fp;
    int i=0, flag;
    if((fp=fopen("cangku.txt","r"))==NULL)
    {
        printf("不能打开文件，文件读取失败！\n");
        return;
    }
    while(1)
    {
        flag=fscanf(fp, "%s %s %d",goods[i].name,
                    goods[i].xh, &goods[i].num);
        if(flag == EOF)
            break;
        i++;
    }
    goods_num = i;
    fclose(fp);
}

void save_txt()
{
    FILE * fp;
    int i;
    if((fp=fopen("cangku.txt","w"))==NULL)
    {
        printf("不能打开文件，文件保存失败！\n");
        return;
    }
    for(i=0; i<goods_num; i++)
        fprintf(fp, "%s %s %d\n",goods[i].name, goods[i].xh,
                goods[i].num);
    fclose(fp);
}

void add()  //入库
{
    int k=-1,n;
    char str1[20],str2[20];
    printf("请输入入库货物名称：");
    scanf("%s",str1);
    printf("请输入入库货物型号：");
    scanf("%s",str2);
    printf("请输入入库货物数量：");
    scanf("%d",&n);
    for(int i=0; i<goods_num; i++)
    {
        if((strcmp(str1,goods[i].name) == 0)&&(strcmp(str2,goods[i].xh)==0)) //比较货物的名称和型号是否和输入的都一样，如果都一样则在原有基础上增加数量n
        {
            goods[i].num=goods[i].num+n;
            k = i;
        }
    }
    if(k==-1) //货物的名称和型号和输入的都不一样，新建一个新的货物，数量为n
    {
        strcpy(goods[goods_num].name,str1);
        strcpy(goods[goods_num].xh,str2);
        goods[goods_num].num=n;
        goods_num++;
    }
    printf("入库成功！\n");
}

void del() //出库 原理和入库类似
{
    int k=-1,n;
    char str1[20],str2[20];
    printf("请输入出库货物名称：");
    scanf("%s",str1);
    printf("请输入出库货物型号：");
    scanf("%s",str2);
    printf("请输入出库货物数量：");
    scanf("%d",&n);
    for(int i=0; i<goods_num; i++)
    {
        if((strcmp(str1,goods[i].name) == 0)&&(strcmp(str2,goods[i].xh)==0)) //找到出库货物
        {
            goods[i].num=goods[i].num-n;
            if(goods[i].num==0) //若出库后数量为0，则删除该货物
            {
                goods_num--; //总货物数减1
                for(int j=i; j<goods_num; j++)
                    goods[j] = goods[j+1];  //把位于该货物后的所有货物向前移一位
            }
            printf("出库成功！\n");
            k = i;
        }
    }
    if(k==-1)
    {
        printf("该型号货物不存在！出库失败！\n");
    }
}

void display()
{
    int i;
        if(goods_num>0)
        {
            printf("货物名称\t型号\t数量\n");
            for(i=0; i<goods_num; i++)
                printf("%-16s%s\t%d\n",goods[i].name,goods[i].xh,goods[i].num);
        }
        else
            printf("货物信息为空！");
}

int main()
{
    while(1)
    {
        load_txt();
        int choice;
        printf("\n欢迎使用物品货物进销存系统\n");
        printf("----------------------\n");
        printf("1.显示存货列表\n");
        printf("2.入库\n");
        printf("3.出库\n");
        printf("0.退出程序\n");
        printf("-----------------------\n");
        printf("请选择功能模块，输入数字0-3：");
        while(1)
        {
            scanf("%d",&choice);
            if(choice>=0&& choice<=3)
                break;
            else
                printf("输入数字不正确，请重输入0-3：");
        }
        switch(choice)
        {
        case 1:
            display();
            break;
        case 2:
            add();
            break;
        case 3:
            del();
            break;
        case 0:
            exit(0);
        }
        save_txt();
    }

}
