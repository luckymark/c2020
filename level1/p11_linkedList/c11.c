#include<stdio.h>
#include <malloc.h>

typedef struct MyStruct
{
	int value;
	struct MyStruct *next;
}LinkList;
LinkList* creat(int n) {
	LinkList* head, * node, * end;//定义头节点，普通节点，尾部节点；
	head = (LinkList*)malloc(sizeof(LinkList));//分配地址
	end = head;         //若是空链表则头尾节点一样
	for (int i = 0; i < n; i++) {
		node = (LinkList*)malloc(sizeof(LinkList));
		printf("请输入第%d个节点的数值:",(i + 1));
		scanf("%d", &node->value);
		end->next = node;
		end = node;
	}
	end->next = NULL;//结束创建
	return head;
}
LinkList* reverse(LinkList* head) {
	LinkList* p1 = NULL;
	LinkList* p2 = NULL;
	LinkList* p3 = NULL;
	
	p1 = head->next;
	p2 = p1;
	while (p2 != NULL)
	{
		p1 = p1->next;
		p2->next = p3;
		p3 = p2;
		p2 = p1;
		
	};
	head->next = p3;//头指针指向最后一项
	return head;
}
int find5(LinkList* head) {
	int j = 1;
	LinkList* p = head;
	p = p->next;
	while (p != NULL) {
		if (p->value == 5) {
			return j;
		}
		p = p->next;
		j++;
	}
	return EOF;
}
int findsecond5(LinkList* head) {
	int j = 1;
	LinkList* p = head;
	p = p->next;
	int first5 = 0;
	while (p != NULL) {
		
		if (p->value == 5&& first5 == 1) {
			return j;
		}
		if (p->value == 5) {
			first5 = 1;
		}
		p = p->next;
		j++;
	}
	return EOF;
}
void print(LinkList* head) {
	LinkList* p = head;
	int j = 1;
	p = p->next;  //不打印头节点的数据域中的值 
	while (p != NULL) {
		printf("%d %d\n", j, p->value);
		p = p->next;
		j++;
	}
}
int main() {
	int n;
	LinkList* head = NULL;   //创建头指针 
	printf("请输入你想要创建的节点个数：\n");
	scanf("%d", &n);
	head = creat(n);
	print(head);
	head = reverse(head);
	print(head);
	int site = find5(head);
	int site2 = findsecond5(head);
	if (site!=EOF)
	{
		printf("第一个5的节点是：%d\n",site);
		if (site2 != EOF)
		{
			printf("第二个5的节点是：%d\n", site2);
		}
		else
		{
			printf("没有第二个为5的节点");
		}
	}
	else
	{
		printf("没有为5的节点");
	}
}

