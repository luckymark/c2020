#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
FILE *fp;
FILE *fp1; 
typedef struct Node{
	char type[16];
	int num;
	Node *next;
}Node;
Node *head=NULL,*end=NULL;
Node *createNode(char *type,int num)
{
	Node *temp=(Node *)malloc(sizeof(Node));
	strcpy(temp->type,type);
	temp->num=num;
	temp->next=NULL;
	return temp;
}
void add(char *type,int num)
{
	Node *newNode=createNode(type,num);
	if(head==NULL) {head=newNode;end=newNode;}
	else 
	{
		end->next=newNode;
		end=newNode;
	}
}
void printmenu()
{
	printf("**************************\n");
	printf("*                        *\n");
	printf("*  显示存货列表-------1  *\n");
	printf("*  货物入库-----------2  *\n");
	printf("*  货物出库-----------3  *\n");
	printf("*  退出程序-----------4  *\n");
	printf("*                        *\n");
	printf("**************************\n");
	printf("\n请输入数字以执行相应的功能");
}
void browse()
{
	system("cls");
	Node *p=head;
	printf("按回车键以回到菜单界面\n");
	printf("type            num\n");
	while(p!=NULL)
	{
		printf("%-16s%d\n",p->type,p->num);
		p=p->next;
	}
	getchar();
	system("cls");
}
void warehouse()
{
	system("cls");
	printf("请输入货物的型号和数量（以空格分隔）：\n");
	char type[16];
	int num;
	scanf("%s%d",type,&num);
	Node *p=head;
	while(p!=NULL) 
	{
		if(strcmp(type,p->type)==0)
		{
			p->num+=num;
			break;
		}
		p=p->next;
	}
	if(p==NULL) add(type,num);
	printf("\n\n货物成功入库！！按回车键以回到菜单界面");
	getchar();getchar();
	system("cls");
}
void deleteNode(Node *deletepos,Node *lastpos)
{
	if(lastpos==NULL)
	{
		Node *temp=head;
		head=head->next;
		if(head==NULL) end=NULL;
		free(temp);
	}
	else
	{
		lastpos->next=deletepos->next;
		if(lastpos->next==NULL) end=lastpos;
		free(deletepos);
	}
}
void outofstock()
{
	system("cls");
	printf("请输入货物的型号及出库量（以空格分隔）：\n");
	char type[16];
	int num;
	scanf("%s%d",type,&num);
	Node *p=head,*lastNode=NULL;
	while(p!=NULL) 
	{
		if(strcmp(type,p->type)==0)
		{
			if(num>p->num)
			{
				printf("\n\n货物储量不足！按回车键以回到菜单界面");
				getchar();getchar();
				system("cls");
				return ;
			}
			else
			{
				p->num-=num;
				if(p->num==0) deleteNode(p,lastNode);
				break;
			}
		}
		lastNode=p;
		p=p->next;
	}
	if(p==NULL) printf("\n\n仓库中无此货物!按回车键以回到菜单界面");
	else printf("\n\n货物成功出库！按回车键以回到菜单界面");
	getchar();getchar();
	system("cls");
}
void scantext()
{
	char type[16];
	int num;
	while(fscanf(fp,"%s%d",type,&num)==2) add(type,num);
}
void exitprogram()
{
	system("cls");
	Node *p=head;
	while(p!=NULL)
	{
		fprintf(fp1,"%-16s%d\n",p->type,p->num);
		p=p->next;
	}
	fclose(fp);fclose(fp1);
	remove("data.txt");
	rename("datatemp.txt","data.txt");
	printf("\n\n成功保存数据，按回车键退出程序");
	exit(0);
}
void start()
{
	scantext();
	while(1)
	{
		printmenu();
		char ch;
		do
		{
			ch=getch();
		}while(ch<'1'||ch>'4');
		switch(ch)
		{
			case '1':
				browse();break;
			case '2':
				warehouse();break;
			case '3':
				outofstock();break;
			case '4':
				exitprogram();break;
		}
	}
}
int main()
{
	fp=fopen("data.txt","r+");
	fp1=fopen("datatemp.txt","w");
	if(fp==NULL)
	{
		printf("读取数据失败，请将数据文件\"data.txt\"置于程序处，然后重新运行程序");
		fclose(fp1);remove("datatemp.txt");
	}
	else start();
	return 0;
}

