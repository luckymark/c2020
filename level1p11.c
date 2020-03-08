#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXN 1000
#define key 5
struct node
{
	int val,id;
	struct node *nxt;
};
struct node *reverse(struct node *hd)
{
	struct node *p=NULL,*q=NULL;
	while(hd)
	{
		p=hd;
		hd=p->nxt;
		p->nxt=q;
		q=p;
	}
	return p;
}
void print(struct node *hd)
{
	for(struct node *tmp=hd;tmp;tmp=tmp->nxt)
		printf("%d ",tmp->val);
	puts("");
}
struct node *find(struct node *hd,int val)
{
	for(struct node *tmp=hd;tmp;tmp=tmp->nxt)
	{
		if(val==tmp->val)
			return tmp;
	}
	struct node *ret=(struct node *)malloc(sizeof(struct node));
	ret->id=-1;
	ret->nxt=NULL;
	ret->val=0;
	return ret;
}
int main()
{
	struct node *head,*pre;
	int n;
	scanf("%d",&n);
	for(int i=1,v;i<=n;i++)
	{
		scanf("%d",&v);
		struct node *tmp=(struct node *)malloc(sizeof(struct node));
		tmp->val=v;
		tmp->id=i;
		tmp->nxt=NULL;
		if(i==1)head=tmp;
		else pre->nxt=tmp;
		pre=tmp;
	}
	print(head);
	print(head=reverse(head));
	printf("%d\n",find(head,5)->id);
	if(find(head,5)->nxt)printf("%d\n",find(find(head,5)->nxt,5)->id);
} 
