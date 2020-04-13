#include <stdio.h>
#include <stdlib.h>
void getdata(int num);
void putdata(int j);
void ListReverse();
struct node
{
    int data;
    struct node *next;
    
};
int Seek(struct node *L);
struct node *head,*p,*q,*t,*record;//record是用来记录第一个存入数据为5节点的下一个节点
int num_2=0;//用来记录节点序号
int main()
{
    int i,n,a;
    printf("请输入一个数\n");
    scanf("%d",&n);
    printf("请输入数据\n");        
    head=NULL;
    for(i=0;i<n;++i)
    {
        scanf("%d",&a);
        getdata(a);
    }
    putdata(n);
    printf("\n%d",Seek(head));
    printf("\n%d",Seek(record));
    ListReverse();
    printf("\n");
    putdata(n);
    return 0;
}

void getdata(int num)
{
    p=(struct node *)malloc(sizeof(struct node));
    p->data=num;
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

void putdata(int j)
{
    t=head;
    for(j;j>0;--j)
    {
    printf("%d ",t->data);
    t=t->next;
    }
}

void ListReverse()
{
    struct node *p=head;
    struct node *q=p->next;
    struct node *g=q->next;
    while(g)
    {
        q->next=p;
        p=q;
        q=g;
        g=q->next;
    }
    q->next=p;
    head->next=NULL;
    head=q;
}

int Seek(struct node *L)
{
    while(L)
    {
    	num_2++;
    	if(L->data==5)
    	{
    		record=L->next;
    		return num_2;
		}
		L=L->next;
	}
	return -1;
}
