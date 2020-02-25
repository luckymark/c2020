#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

struct node{
	int id,val;
	node *fa,*son[2];
};
node *rt;
int cnt = 0;
void rotate(node* r,int s)
{
	node *p, *q;
	
	q = r->son[s ^ 1];
	p = q->son[s];
	
	if(p != NULL) 
	p->fa = r;
	r->son[s ^ 1] = p;
	q->son[s] = r;
	
	q->fa = r->fa;
	r->fa = q;
	if(q->fa != NULL)
	{
		if(q->fa->son[0] == r)
		q->fa->son[0] = q;
		else
		q->fa->son[1] = q;
	}
}

void splay(node* p1,node* fa)
{
	node *p, *q, *r;
	int x, y;
	p = p1;
	while(p->fa!=fa)
	{
		x = y = 0;
		q = p->fa;
		r = q->fa;
		if(q->son[1] == p) x = 1;
		if(r!=NULL&&r->son[1] == q) y = 1;
		if(r == fa)
		rotate(q, x ^ 1);
		else
		{
			if(x ^ y)
			{
				rotate(q, x ^ 1);
				rotate(r, y ^ 1);
			}
			else
			{
				rotate(r, y ^ 1);
				rotate(q, x ^ 1);
			}
		}
	}
	if(fa == NULL) rt = p1;
}

node *pos;
node* insert(node* p, int id, int val,node* fa)
{
	if(p == NULL)
	{
		p = (node*)malloc(sizeof(node));
		p->id = id;
		p->val = val;
		p->fa = fa;
		p->son[0] = p->son[1] = NULL;
		pos = p;
		cnt++;
		return p;
	}
	if(p->id == id) 
	{
		p->val += val;
		return p;
	}
	if(p->id > id)
	p->son[0] = insert(p->son[0], id, val, p);
	else 
	p->son[1] = insert(p->son[1], id, val, p);
	return p;
}

void load_data()
{
	FILE *fin;
	int n, i;
	
	fin = fopen("ware.txt", "r");
	fscanf(fin,"%d",&n);
	cnt = n;
	for(i = 1;i <= n;i++)
	{
		int id,val;
		fscanf(fin,"%d%d", &id, &val);
		rt = insert(rt, id, val,NULL);
		splay(pos, NULL);
	}
	fclose(fin);
}


void pf(node *p)
{
	if(p ==NULL) return;
	pf(p->son[0]);
	printf("id:%d num:%d\n", p->id, p->val);
	pf(p->son[1]);
	return;
}

node* find(node *p, int id)
{
	if(p == NULL) return NULL;
	if(p->id == id)
	return p;
	return find(p->son[p->id < id], id);
}

node* find_pre(node *p,int id, node *fa)
{
	if(p == NULL)
	return fa;
	return find_pre(p->son[id > p->id], id, p);
}
void del(int id)
{
	node *p = find(rt, id), *q;
	if(p == NULL) 
	{
		printf("¸Ã»õÎï²»´æÔÚ\n");
		return;
	}
	cnt--;
	splay(p, NULL);
	q = NULL;
	if(p->son[0] == NULL) 
	{
		rt = p->son[1];
		free(p);
		if(rt == NULL) return;
		p->son[1]->fa = NULL;
		return;
	}
	q = find_pre(rt->son[0], p->id, NULL);
	splay(q, NULL);
	rt = q;
	p->son[1]->fa = q;
	q->son[1] = p->son[1];
	q->fa = NULL;
	free(p);
	printf("successful\n");
}

void Save_pf(FILE *fout, node* p)
{
	if(p == NULL) return;
	Save_pf(fout, p->son[0]);
	fprintf(fout,"%d %d\n", p->id, p->val);
	Save_pf(fout, p->son[1]);
}
void Save()
{
	FILE *fout;
	fout = fopen("ware.txt","w");
	fprintf(fout,"%d\n",cnt);
	Save_pf(fout,rt);
	printf("successful\n");
	
}
int main(void)
{
	rt = NULL;
	load_data();
//	pf(rt);
	while(1)
	{
		printf("Êý¾Ý½«´æ´¢ÔÚware.txtÖÐ\n1ÏÔÊ¾´æ»õÁÐ±í\n2Èë¿â\n3³ö¿â\n4ÍË³ö³ÌÐò\n");
		char c = getch();
//		int c;
//		scanf("%d", &c);
		if(c == '1')
		{
			pf(rt);
			printf("successful\n");
		}
		else if(c == '2')
		{
			int id,num;
			scanf("%d%d", &id, &num);
			rt = insert(rt, id, num, NULL);
			printf("successful\n");
		}
		else if(c == '3')
		{
			int id;
			scanf("%d", &id);
			del(id);
		}
		else if(c == '4')
		{
			Save();
			break;
		}
		printf("°´ÈÎÒâ¼ü¼ÌÐø\n");
		char ch = getch();
		system("cls");
	}
 } 
