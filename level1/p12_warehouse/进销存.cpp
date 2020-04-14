#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
struct node
{
	int type;
	int data;
	struct node *next;
};
FILE *fp=NULL;
struct node *head,*q,*p,*t;
void menu();
int WriteIn_List();
void WriteIn_Txt();
void ShowGoods();
void InGoods();
void OutGoods();
int main()
{
	int n;
	menu();
	WriteIn_List();
	scanf("%d",&n);
	system("cls");
	while(n>=1&&n<4)
	{
		if(n==1)
		{
			ShowGoods();
			printf("请输入你想执行的数字:");
			scanf("%d",&n);
			system("cls");
		}
		else if(n==2) 
		{
			InGoods();
			printf("请输入你想执行的数字:");
			scanf("%d",&n);
			system("cls");
		}
		else if(n==3)
		{
			OutGoods();
			printf("请输入你想执行的数字:");
			scanf("%d",&n);
			system("cls"); 
		}
	}
	printf("感谢您的使用!");
	WriteIn_Txt();
	fclose(fp);
	return 0;
} 

void menu()
{
	printf("\t\t\t\t  欢迎来到进销存系统\n");
	printf("-------------------------------------------------------------------------------------------------------------\n");
	printf("显示存货列表:1\n");
	printf("入库:2\n");
	printf("出库:3\n");
	printf("退出程序:4\n");
	printf("请输入你想执行的数字:");
}

int WriteIn_List()
{
	head=NULL;
	fp=fopen("data.txt","r+");
	while(!feof(fp))
	{

			p=(struct node*)malloc(sizeof(struct node));
			fscanf(fp,"%d",&p->type);
			fscanf(fp,"%d",&p->data);
			p->next=NULL;
			if(head==NULL)
			{
				head=p;
			}
			else
			{
				q->next=p; 
			}
			q=p;
	
	}

}

void ShowGoods()
{
	t=head;
	printf("型号  数量\n");
	while(t!=NULL)
	{
		
		printf("%d    ",t->type);
		printf("%d\n",t->data); 
		t=t->next;
	}
}

void InGoods()
{

	int type_1,data_1;
	printf("请输入型号:"); 
	scanf("%d",&type_1);
	printf("\n请输入数量:");
	scanf("%d",&data_1);
	t=head;
	while(t!=NULL)
	{
		if(t->type==type_1)
		{
			t->data+=data_1;
			break;
		}
		else if(t->next==NULL && t->type!=type_1)
		{	
			p=(struct node*)malloc(sizeof(struct node));
			t->next=p;
			p->next=NULL;
			p->type=type_1;
			p->data=data_1;
			break;
		}
		t=t->next;
	}
	if(head==NULL)
	{
		q=(struct node*)malloc(sizeof(struct node));
		q->data=data_1;
		q->type=type_1;
		q->next=NULL;
		head=q;
	}
}

void OutGoods()
{
	int type_2,data_2;
	printf("请输入型号:"); 
	scanf("%d",&type_2);
	printf("\n请输入要减少的数量:");
	scanf("%d",&data_2);
	t=head;
	while(t!=NULL)
	{
		if(t->type==type_2)
		{
			t->data-=data_2;
			if(t->data<=0)
			{
				t->data=0;
			}
			break;	
		}
		t=t->next;
	}
}

void WriteIn_Txt()
{
	FILE *w=fopen("data.txt","w+");
	t=head;
	while(t!=NULL)
	{
		fprintf(w,"%d ",t->type);
		fprintf(w,"%d ",t->data);
		t=t->next; 
	}
	fclose(w);
}
