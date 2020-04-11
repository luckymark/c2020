#include<stdio.h> 
#include<stdlib.h>
typedef struct Node{
	int value;
	Node *next;
}Node;
Node *head=NULL;
Node *createNode(int data)
{
	Node *temp=(Node *)malloc(sizeof(Node));
	temp->value=data;
	temp->next=NULL;
	return temp;
}
void add(int data)//在链表尾部添加一个结点 
{
	Node *newNode=createNode(data);
	if(head==NULL) head=newNode;
	else
	{
		Node *p=head;
		while(p->next!=NULL) p=p->next;
		p->next=newNode;
	}
}
void insert(int data,int pos)//在第pos个结点之后插入一个结点 
{
	Node *newNode=createNode(data);
	int cnt=1;
	Node *p=head;
	while(cnt<pos&&p->next!=NULL)
	{
		p=p->next;
		cnt++;
	}
	if(cnt<pos) printf("链表结点总数小于%d!!\n",pos);
	else
	{
		newNode->next=p->next;
		p->next=newNode;
	}
}
void deletepos(int pos)//删除序号为pos的结点 
{
	if(head==NULL)
	{
		printf("链表为空!!\n");
		return ;
	}
	if(pos==1)//如果删除第一个结点 
	{
		Node *temp=head;
		head=head->next;
		free(temp);
		return ;
	}
	Node *p=head;
	int cnt=2;
	while(p!=NULL&&cnt<pos)
	{
		cnt++;
		p=p->next;
	}
	if(p==NULL||p->next==NULL)
	{
		printf("链表结点总数小于%d!!\n",pos);
		return ;
	}
	Node *nextNode=p->next;
	p->next=nextNode->next;
	free(nextNode);
}
void alldelete()//将链表结点全部删除 
{
	Node *p=head;
	head=NULL;
	while(p!=NULL)
	{
		Node *temp=p;
		p=p->next;
		free(temp);
	}
}
void traverse() //遍历并输出每个节点的value 
{
	Node *p=head;
	while(p!=NULL)
	{
		printf("%d ",p->value);
		p=p->next;
	}
}
void reverse()//将所有结点反序 
{
	if(head==NULL||head->next==NULL) return ;//没有结点或只有1个结点，直接返回 
	Node *nowNode=head;
	Node *nextNode=head->next;
	head->next=NULL;
	while(nextNode!=NULL)
	{
		Node *nextnextNode=nextNode->next;
		nextNode->next=nowNode;
		nowNode=nextNode;
		nextNode=nextnextNode;
	}
	head=nowNode; 
}
int findkth(int num,int kth)//寻找第k个value为num的结点，并返回其序号，若找不到则返回-1 
{
	int cnt=0,k=0;
	Node *p=head;
	while(p!=NULL) 
	{
		cnt++;
		if(p->value==num)
		{
			k++;
			if(k==kth) return cnt;
		}
		p=p->next;
	}
	return -1;
}
int main()
{
	for(int i=1;i<=10;i++) add(2*i-1);
	for(int i=10;i>=1;i--) insert(-2*i,i);
	//alldelete();
	//deletepos(5);
	//reverse();
	traverse();
	int pos=findkth(5,2);
	//printf("\n%d",pos);
	return 0;
}
