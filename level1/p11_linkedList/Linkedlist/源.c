#include<stdio.h>
#include<stdlib.h> 

typedef struct node
{
	int data;
	struct node* next = NULL;
}node;


node* create();
node* append();


int main()
{

	node* header = create();
	node* p = NULL;
	node* q;
	q = (node*)malloc(sizeof(node));

	while (header->data >= 0 || header->data < 0)
	{
		p = append();
		while (p->data >= 0 || p->data < 0)
		{
			p = append();
		}
		break;
	}

	return 0;

}


node* create()
{
	node* header;
	node* p;
	node* q;
	header = (node*)malloc(sizeof(node));
	p = (node*)malloc(sizeof(node));
	q = (node*)malloc(sizeof(node));
	printf("请输入需要存储的数字。");
	scanf_s("%d", &(p->data));
	p->next = NULL;
	header = p;
	q = p->next;
	while (header->data >= 0 || header->data < 0)
	{
		p = q;
		printf("请输入需要存储的数字。");
		scanf_s("%d", &(p->data));
		q = p->next;
	}
}
