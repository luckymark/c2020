#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define For(x,a,b) for(x=a;x<=b;x++)
int i,i1,i2;
typedef struct node{//定义结构类型以实现链表，顺便自定义类型名称 
	int value;
	struct node* next;
}Node; 
Node *create(Node *p,int N);//初始化链表 
void output(Node *p);//遍历输出链表 
Node *length(int N);//辅助函数，便于其他操作的进行 
void search(Node *p);//直接查找所有值为5的节点吧，多实现点功能也没什么不好的 
void reverse(Node *p);//将该链表所有节点反序 
int main(void)
{
    int n;
    printf("请输入需要创建的链表的长度：\n");
    scanf("%d",&n);
    Node *head=length(n);
    output(head);
    reverse(head);
    search(head);
	system("pause");
	return 0;
}
Node *create(Node *p,int N)
{
    if(N!=0) scanf("%d",&(*p).value);
    if(N==2){
        (*p).next=NULL;
        return NULL;
    }
    Node *pre=(Node *)malloc(sizeof(Node));
    (*p).next=pre;
    return pre;
}
void output(Node *p)
{
    system("CLS");
    int count=0;
    while(p!=NULL){
        if(count==0)
        {
            p=(*p).next;
            count++;
            continue;
        }
        count++;
		printf("Node%d:%5d\n",count,(*p).value);
        p=(*p).next;
    }
}
Node *length(int N)
{
    Node *head=(Node *)malloc(sizeof(Node));
    Node *a=(Node *)malloc(sizeof(Node));
    For(i,0,N){
        if(i==0) a=create(head,0);//创建首个节点 
        else if(i==N) a=create(a,2);
        else a=create(a,1);
    }
    return head;
}
void search(Node *p)
{
    system("CLS");
    int count=0;
    while(p!=NULL){
        if(count==0){
            p=(*p).next;//p后移 
            count++;
            continue;
        }
        if((*p).value==5){
            count++;
			printf("Node%d:%p\n",count,p);
            p=(*p).next;
        }
        else{
            count++;
            p=(*p).next;
        }
    }
}
void reverse(Node *p)
{
    system("CLS");
    Node *rev,*old;//怎么说呢……old当作一种媒介吧？ 
    Node *head=p;
    int count=0;
    while((*p).next!=NULL){
        if(count==0){
            p=(*p).next;//p后移 
            rev=(*p).next;//rev存储p之后的节点 
            (*p).next=NULL;
            old=p;
            p=rev;
            count++;
            continue;
        }
        rev=(*p).next;//头大，懒得写注释了QAQ 
        (*p).next=old;
        old=p;
        p=rev;
    }
    (*p).next=old;
    (*head).next=p;
    output(head);
}
