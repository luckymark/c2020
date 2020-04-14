#include<stdio.h>
#include<stdlib.h> 


typedef struct node
{
	int seq;
	int data;
	struct node * next = NULL;
}node;


node* create(FILE* fp);
void Print(node * header);
void append(node * header);
void output(node * header);
void keep(node* header, FILE* fp);


int main()
{
	int order;
	errno_t err;
	FILE* fp;
	 err = fopen_s(&fp, "Inventorydata.txt", "r+");
	node * header = NULL;
	header = create(fp);
	fclose(fp);
	printf("1:显示存货列表 (按1执行)\n");
	printf("2:入库 (按2执行)\n");
	printf("3:出库 (按3执行)\n");
	printf("4:退出程序 (按4执行)\n");
	printf("请输入你想执行的数字：\n");
	scanf_s("%d", &order);
	while (order < 4 && order >= 1)
	{
		switch (order)
		{
		case 1: Print(header);
			printf("请输入你想执行的数字：");
				scanf_s("%d", &order);
				break;
		case 2: append(header);
			printf("请输入你想执行的数字：");
				scanf_s("%d", &order);
				break;
		case 3: output(header);
			printf("请输入你想执行的数字：");
				scanf_s("%d", &order);
				break;
		case 4: break;
		default: printf("error");
		}

	}
	err = fopen_s(&fp, "Inventorydata.txt", "w+");
	keep(header,fp);
    printf("库存数据已保存并退出");
}


node* create(FILE* fp)
{
	node* header = NULL;
	node* p = (node*)malloc(sizeof(node));
	p->next = NULL;
	fscanf_s(fp, "%d", &p->seq);
	fscanf_s(fp, "%d", &p->data);
	header = p;
	while (fgetc(fp) != EOF)
	{
		p->next = (node*)malloc(sizeof(node));
		p = p->next;
		fscanf_s(fp, "%d", &p->seq);
		fscanf_s(fp, "%d", &p->data);
	}
	p->next = NULL;
	return header;
}

void append(node * header)
{
	int order;
	int num=0;
	int sum = 0;
	int n;
	node* p = NULL;
	p = header;
	while (p != NULL)
	{
		sum++;
		p = p->next;
	}
	p = header;
	printf("请输入你想入库的货物型号：");
	scanf_s("%d", &order);
	if (order <= sum)
	{
		printf("请输入你想入库的数量：");
		scanf_s("%d", &num);
		for (n = 1; n < order; n++)
		{
			if (p != NULL)
			{
				p = p->next;
			}
		}
		p->data = p->data + num;

	}
	else
	{
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = (node*)malloc(sizeof(node));
		p = p->next;
		scanf_s("%d", &p->seq);
		scanf_s("%d", &p->data);
		p -> next = NULL;
	}
}


void output(node* header)
{
	int order;
	int num;
	int sum = 0;
	int n;
	node* p;
	p = header;
	while (p != NULL)
	{
		sum++;
		p = p->next;
	}
	p = header;
	printf("请输入你想出库的货物型号：");
	scanf_s("%d", &order);
	if (order <= sum)
	{
		printf("请输入你想出库的数量：");
		scanf_s("%d", &num);
		for (n = 1; n < order; n++)
		{
			if (p != NULL)
			{
				p = p->next;
			}
		}
		p->data = p->data - num;

	}
	else printf("Error:该库存中不存在该货物序号");

}

void keep(node* header, FILE* fp)
{
	node* p;
	if (header == NULL)
	{
		printf("link is null\n");
	}
	p = header;
	while (p != NULL)
	{
		fprintf(fp, "%d", p->seq);
		fprintf(fp, "%d", p->data);
		p = p->next;
	}
}


void Print(node * header)
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
		printf("the %dth good is %d\n", ++index, p->data);
		p = p->next;
	}
}