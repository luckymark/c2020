#include<stdio.h>
#include<stdlib.h> 
#include<conio.h>
#define findnum 5

typedef struct node 
{
	int data;
	struct node* next = NULL;
}node;


node * create();
node * reverse(node * header);
int  find(node* header);
void Print(node* header);
int find2(node* header);


int main()
{
	int num;
	int decide;
	node* header;
	header = create();
	//Print(header);  检验链表是否成功生成
	printf("如果你想将链表中节点全部反序(请输入1，反之输入2):  \n");
	scanf_s("%d", &decide);
	if (decide == 1)
	{
		header = reverse(header);
	}
	//Print(header);   检验是否成功反序
	printf("第一个值为5的序号节点为：%d  (若值为-1则表示改链表中不存在5) \n ", find(header));
	printf("第二个值为5的序号节点为：%d  (若值为-1则表示改链表中不存在5) ", find2(header));

	return 0;

}


node* create()
{
	node* header = NULL;
	node* p = (node*)malloc(sizeof(node));
	p->next = NULL;
	header = p;
	printf("请输入需要存储的数字(如果想退出输入，请输入-1):");
	if (scanf_s("%d", &(p->data)) == 0) {
		free(p);
		return NULL;
	}
	while (p->data != -1)
	{
		p->next = (node*)malloc(sizeof(node));
		p = p->next;		
		printf("请输入需要存储的数字(如果想退出输入，请输入-1):");		
		if (p == NULL) {
			exit(-11);
		}
		scanf_s("%d", &(p->data));	
	}  
	p->next = NULL;
	return header;
}

node* reverse(node* header)
{
	node* p, * q, * r;
	if (header->next == NULL)
	{
		return NULL;
	}
	p = header;
	q = p->next;
	p->next = NULL;
	while (q != NULL)
	{
		r = q->next;
		q->next = p;
		p = q;
		q = r;
	}
	header = p->next;
	return header;
}


int find(node* header)
{
	node* p;
	int num=0;
	if (header == NULL)
	{
		printf("link is null\n");
	}
	p = header;
	while (p != NULL)
	{
		num++;
		if (p->data == findnum)
		{
			return num;
		}
		p = p->next;
	}
	return -1;
}

int find2(node* header)
{
	node* p;
	int num = 0;
	int a=0;
	if (header == NULL)
	{
		printf("link is null\n");
	}
	p = header;
	while (p != NULL)
	{
		num++;
		if (p->data == findnum)
		{
			a++;
		}
		if (a == 2)
		{
			return num;
		}
		p = p->next;
	}
	return -1;
}


void Print(node* header)
{
	int index = 0;
	node* p;
	if (header == NULL)
	{
		printf("link is null\n");
	}
	p = header;
	while (p != NULL)
	{
		printf("the %dth node is %d\n", ++index, p->data);
		p = p->next;
	}
}


