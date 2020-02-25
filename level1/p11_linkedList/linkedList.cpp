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
	fscanf(fin,"%d", &n);
	for(i = 1;i <= n;i++)
	{
		int num, val;
		fscanf(fin,"%d%d", &num, &val);
		insert(val, num);
	}
}

void pf()
{
	printf("\n");
	node* p = rt;
	while(p!=NULL)
	{
		printf("val:%d num:%d\n", p->val, p->num);
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
	printf("-1");
}
int main(void)
{
	rt = back = NULL;
	build();
	while(1)
	{
		char c = getch();
		if(c == '1')
		{
			rev(rt, NULL);
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
	}
}
