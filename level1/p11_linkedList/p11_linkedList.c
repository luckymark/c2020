#include <stdio.h>
#include <stdlib.h>
#define diaoqu (list*)malloc(sizeof(list))//偷个懒
typedef struct stu
{
    int num;
    struct stu *next;
} list;
//创建一个列表
list *creat(int n)
{
    list *head,*node,*end;
    head =diaoqu;
    end=head;
    for(int i = 0; i < n ; i++)
    {
        node=diaoqu;
        scanf("%d",&node->num);
        end->next=node;
        end=node;
        //printf("\nnice!\n");
    }
    end->next=NULL;
    return head;//返回一个地址
}
//反序
list *fan(list *head)
{
    
    list *tem1,*tem2;
    head=head->next;
    if(head->next==NULL) //只有一个节点
    {
        tem1=head;
        head=diaoqu;
        head->next=tem1;
        return head;
    }
    
    else
    {
    	tem1=head->next;
    	head->next=NULL;
    	while(tem1->next!=NULL)
    	{
        	tem2=tem1->next;
        	tem1->next=head;//完成了地址更改
        	head=tem1;
        	tem1=tem2;//全部往右边移动一位
    	}
    	tem1->next=head;
    	head=diaoqu;
    	head->next=tem1;//最后一个节点还没改
    	return head;
    }
}
//对比前后两次。
void tell(list *h)
{
    while (h->next != NULL) 
    {
		h = h->next;
		printf("%d  ", h->num);
	}
    printf("\n");
}
int main()
{
    int a,i;
    scanf("%d",&a);
    list *b=creat(a);
    printf("BEFORE:"),tell(b);
    b=fan(b);
    printf("LATER:"),tell(b);
    i=1;
    while(b->next!=NULL)
    {
        b=b->next;
        if(b->num==5)
        {
            printf(" %d ",i);
        }
        else printf("-1");//这里有点没看懂题意，是没有5才返回-1吗？总之我先按不是5返回-1写了。
        i+=1;
    }
    return 0;
}