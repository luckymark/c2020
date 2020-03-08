#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int num;
    int value;
    struct node* next;
}Node;

Node *init(int n)
{
    Node *head,*div,*end;
    head = (Node*) malloc(sizeof(Node));
    end = head;
    for (int i = 0; i <n ; ++i) {
        div=(Node*)malloc(sizeof(Node));
        scanf("%d",&div->value);
        div->num=i+1;
        end->next=div;
        end = div;
    }
    end->next = NULL;
    return head;

}

void ShowList(Node *list)
{
    Node *t=list;
    while (t->next!=NULL)
    {
        t=t->next;
        printf("%d ",t->value);
    }
    printf("\n");
}
Node *ReverseList(Node *list)
{
    Node *pre=list,
         *cur=pre->next,
         *nxt =NULL;
    if(cur)
    {
        nxt =cur->next;
        pre = NULL;
    } else{return pre;}

    while (1)
    {
        cur->next=pre;

        if(nxt->next!=NULL)
        {

            pre = cur;
            cur = nxt;
            nxt=nxt->next;
        } else{
            nxt->next=cur;
            Node *t=(Node*)malloc(sizeof(Node));
            t->next=nxt;
            return t;
        }

    }

}

Node *searchx(int x,Node* list)
{
    Node* t=list;
    int flag = 1;
    while (t->next!=NULL)
    {
        t=t->next;
        if (t->value==x){
            printf("%d\n",t->num);
            flag = 0;
            return t;
        }
    }
    if (flag) printf("-1\n");
    return NULL;
}
int main()
{
    int n,x;
    printf("Input the size of the list :");
    scanf("%d",&n);
    Node *list = init(n);
    printf("The list: ");
    ShowList(list);
    list=ReverseList(list);
    printf("Reverse it: ");
    ShowList(list);
    printf("Input the number you want to search: ");
    scanf("%d",&x);

    Node *t;
    if((t=searchx(x,list)))
        searchx(x,t);
    getchar();
}