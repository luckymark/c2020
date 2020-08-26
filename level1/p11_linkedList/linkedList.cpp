#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
struct node{
	int val,num;
	node *nxt;
};
node *rt, *back;
node* insert(int val, int num)
{
	node* p = (node*) malloc(sizeof(node));
	p->num = num;
	p->val = val;
	p->nxt = NULL;
	if(rt == NULL)
	{
		rt = p;
		back = p;
		return p;
	}
	else
	{
		back->nxt = p;
		back = p;
		return rt;
	}
}
void build()
{
	int n, i;
	FILE *fin;
	
	fin = fopen("data.txt","r");
	if(fin == NULL) 
	{
		printf("未找到data.txt文件请手工输入\n请输入插入的节点总数\n请输入插入的节点编号和数目\n");
		fin = stdin;
	}
	fscanf(fin,"%d", &n);
	for(i = 1;i <= n;i++)
	{
		int num, val;
		fscanf(fin,"%d%d", &num, &val);
		insert(val, num);
	}
	if(fin != NULL) printf("successful\n");
	system("cls");
}

void pf()
{
	printf("链表各节点的信息如下\n");
	node* p = rt;
	while(p!=NULL)
	{
		printf("val:%d id:%d\n", p->val, p->num);
		p = p->nxt;
	}
}

void rev(node* nw, node* pre)
{
	if(nw->nxt == NULL)
	{
		rt = nw;
		nw->nxt = pre;
		return;
	}
	rev(nw->nxt, nw);
	nw->nxt = pre;
}
void find()
{
	node* p = rt;
	bool flag = false;
	while(p != NULL)
	{
		if(p->val == 5)
		{
			printf("%d ",p->num);
			flag = true;
		}
		p = p->nxt;
	}
	if(!flag)
	printf("未找到值为5的元素");
}
int main(void)
{
	rt = back = NULL;
	printf("从data.txt中导入链表\n");
	build();
	while(1)
	{
		printf("1使链表反序并输出\n2输出链表所有元素\n3查找值为5的元素\n4退出程序\n");
		char c = getch();
		if(c == '1')
		{
			rev(rt, NULL);
			printf("反序后");
			pf();
		}
		else if(c == '2')
		{
			pf();
		}
		else if(c == '3')
		{
			find();
		}
		else if(c == '4') exit(0);
		printf("按任意键继续\n");
		char ch = getch();
		system("cls");
	}
}
