#include <stdio.h>
#include <string.h>
#define BIGNUMBER 1000
typedef struct node{
    char goodstype[101];
    int goodsnum;
}Node;
Node list[BIGNUMBER];
int  ENDOFLIST= -1;

//主页
void HomePage()
{
    printf("\n\n");
    printf("info/1-->显示存货列表\n");
    printf("import/2-->入库\n");
    printf("export/3-->出库\n");
    printf("quit/4-->退出程序\n");
    printf("\n\n");
}
int comparestr(char s1[],char s2[])
{
    if(strlen(s1)!=strlen(s2)) return 0;
    for (int i = 0; i <strlen(s1) ; ++i) {
        if(s1[i]!=s2[i]) return 0;
    }
    return 1;
}
//搜索某商品在列表中的位置
int search(char goodstype[])
{
    int pos=-1;
    for (int i = 0; i <ENDOFLIST+1 ; ++i) {
        if(comparestr(list[i].goodstype,goodstype))
        {
            pos = i;
            break;
        }
    }
    return pos;
}

//列出库存
void PrintInfo()
{
    if (ENDOFLIST==-1){
        printf("仓库空空如也\n");
        return ;
    }
    for (int i = 0; i <ENDOFLIST+1 ; ++i) {
        printf("货物类型:%s  余量:%d\n",list[i].goodstype,list[i].goodsnum);
    }

    return ;
}

//入库
void Import()
{
    int goodsnum;
    int pos=-1;
    char goodstype[101];

    printf("请分别输入货物型号和入库数量：");
    scanf("%s%d",&goodstype,&goodsnum);

    pos = search(goodstype);
    if(pos==-1)
    {
        ENDOFLIST++;
        strcpy(list[ENDOFLIST].goodstype,goodstype);
        list[ENDOFLIST].goodsnum=goodsnum;
        printf("入库成功，当前余量 %s:%d \n",list[ENDOFLIST].goodstype,list[ENDOFLIST].goodsnum);
    } else{
        list[pos].goodsnum+=goodsnum;
        printf("出库成功，当前余量%s:%d\n",list[pos].goodstype,list[pos].goodsnum);
    }
    return;;
}

//出库
void Export()
{
    int num;
    int pos=-1;
    char goodstype[101];

    printf("请分别输入货物型号和出库数量：");
    scanf("%s%d",&goodstype,&num);

    pos = search(goodstype);
    if(pos==-1)
    {
        printf("没有找到该商品\n");
    }
    else{
        if (num<=list[pos].goodsnum) {
            list[pos].goodsnum -= num;
            printf("出库成功，当前余量%s:%d\n",list[pos].goodstype,list[pos].goodsnum);
        }
        else{
            printf("出库失败，仓库余量不足\n");
            printf("当前余量%s:%d",list[pos].goodstype,list[pos].goodsnum);
        }
    }

}

void ReadFromFile()
{
    FILE* fp;
    fp=fopen("D:\\C profile\\p12_warehouse\\data.txt","r");
    if(fp==NULL)
    {
        printf("未找到库存文件\n");
        return ;
    }

    while(!feof(fp))
    {
        ++ENDOFLIST;
        fscanf(fp,"%s %d",&list[ENDOFLIST].goodstype,&list[ENDOFLIST].goodsnum);
    }
    fclose(fp);
    return ;
}
void WriteFile()
{
    FILE* fp;
    fp=fopen("D:\\C profile\\p12_warehouse\\data.txt","w");
    int i;
    for ( i = 0; i <ENDOFLIST ; ++i) {
        fprintf(fp,"%s %d\n",list[i].goodstype,list[i].goodsnum);
    }
    fprintf(fp,"%s %d",list[i].goodstype,list[i].goodsnum);
    fclose(fp);
    return ;

}

int main() {
    ReadFromFile();
    char operateValue[111];
    int quitflag = 0;
    HomePage();
    while (1){
        printf("请选择您的操作：");
        scanf("%s",&operateValue);
        int caseValue;
        if(comparestr(operateValue,"info")||comparestr(operateValue,"1")) caseValue=0;
        else if(comparestr(operateValue,"import")||comparestr(operateValue,"2")) caseValue=1;
        else if(comparestr(operateValue,"export")||comparestr(operateValue,"3")) caseValue=2;
        else if(comparestr(operateValue,"quit")||comparestr(operateValue,"4")) caseValue=3;
        switch(caseValue)
        {
            case 0:
                PrintInfo();
                break;
            case 1:
                Import();
                break;
            case 2:
                Export();
                break;
            case 3:
                quitflag = 1;
                break;
        }
        printf("\n");
        if (quitflag==1) break;
    }
    WriteFile();
    return 0;
}
