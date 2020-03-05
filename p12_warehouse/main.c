#include <stdio.h>
#include <string.h>
#define BIGNUMBER 1000
typedef struct node{
    char goodstype[101];
    int goodsnum;
}Node;
Node list[BIGNUMBER];
int  ENDOFLIST= -1;

//��ҳ
void HomePage()
{
    printf("\n\n");
    printf("info/1-->��ʾ����б�\n");
    printf("import/2-->���\n");
    printf("export/3-->����\n");
    printf("quit/4-->�˳�����\n");
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
//����ĳ��Ʒ���б��е�λ��
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

//�г����
void PrintInfo()
{
    if (ENDOFLIST==-1){
        printf("�ֿ�տ���Ҳ\n");
        return ;
    }
    for (int i = 0; i <ENDOFLIST+1 ; ++i) {
        printf("��������:%s  ����:%d\n",list[i].goodstype,list[i].goodsnum);
    }

    return ;
}

//���
void Import()
{
    int goodsnum;
    int pos=-1;
    char goodstype[101];

    printf("��ֱ���������ͺź����������");
    scanf("%s%d",&goodstype,&goodsnum);

    pos = search(goodstype);
    if(pos==-1)
    {
        ENDOFLIST++;
        strcpy(list[ENDOFLIST].goodstype,goodstype);
        list[ENDOFLIST].goodsnum=goodsnum;
        printf("���ɹ�����ǰ���� %s:%d \n",list[ENDOFLIST].goodstype,list[ENDOFLIST].goodsnum);
    } else{
        list[pos].goodsnum+=goodsnum;
        printf("����ɹ�����ǰ����%s:%d\n",list[pos].goodstype,list[pos].goodsnum);
    }
    return;;
}

//����
void Export()
{
    int num;
    int pos=-1;
    char goodstype[101];

    printf("��ֱ���������ͺźͳ���������");
    scanf("%s%d",&goodstype,&num);

    pos = search(goodstype);
    if(pos==-1)
    {
        printf("û���ҵ�����Ʒ\n");
    }
    else{
        if (num<=list[pos].goodsnum) {
            list[pos].goodsnum -= num;
            printf("����ɹ�����ǰ����%s:%d\n",list[pos].goodstype,list[pos].goodsnum);
        }
        else{
            printf("����ʧ�ܣ��ֿ���������\n");
            printf("��ǰ����%s:%d",list[pos].goodstype,list[pos].goodsnum);
        }
    }

}

void ReadFromFile()
{
    FILE* fp;
    fp=fopen("D:\\C profile\\p12_warehouse\\data.txt","r");
    if(fp==NULL)
    {
        printf("δ�ҵ�����ļ�\n");
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
        printf("��ѡ�����Ĳ�����");
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
