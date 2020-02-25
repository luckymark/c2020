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
	if(fin == NULL) printf("Î´ÕÒµ½data.txtÎÄ¼þÇëÊÖ¹¤ÊäÈë\n"),fin = stdin;
	if(fin == NULL) printf("ÇëÊäÈë²åÈëµÄ½Úµã×ÜÊý\n");
	if(fin == NULL) printf("ÇëÊäÈë²åÈëµÄ½Úµã±àºÅºÍÊýÄ¿\n");
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
	printf("Á´±í¸÷½ÚµãµÄÐÅÏ¢ÈçÏÂ\n");
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
	printf("Î´ÕÒµ½ÖµÎª5µÄÔªËØ");
}
int main(void)
{
	rt = back = NULL;
	printf("´Ódata.txtÖÐµ¼ÈëÁ´±í\n");
	build();
	while(1)
	{
		printf("1Ê¹Á´±í·´Ðò²¢Êä³ö\n2Êä³öÁ´±íËùÓÐÔªËØ\n3²éÕÒÖµÎª5µÄÔªËØ\n4ÍË³ö³ÌÐò\n");
		char c = getch();
		if(c == '1')
		{
			rev(rt, NULL);
			printf("·´Ðòºó");
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
		printf("°´ÈÎÒâ¼ü¼ÌÐø\n");
		char ch = getch();
		system("cls");
	}
}
