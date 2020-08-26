#include<stdio.h>
#include<malloc.h>

typedef struct node Node;
struct node{
    int value;
    struct node* next;
}*temp;
Node* Insert(Node *head,Node *tail,int value);
void output(Node*head);
Node* fanxu(Node*head);
int search1(Node* head);
int search2(Node* head);

int main(){
    //创建并赋值一个链表
    Node *tail=NULL;
    Node *head=(Node*)malloc(sizeof(Node));
    for(int i=0;i<10;i++){
        tail=Insert(head,tail,i);
    }
    output(head);//输出

    //节点反序并输出
    Node* newHead=fanxu(head);
    head->next=NULL;
    output(newHead);
    
    printf("%d\n",search1(newHead));//查找结点
    printf("%d\n",search2(newHead));

    return 0;
    
}

Node* Insert(Node *head,Node *tail,int value){
    if(tail==NULL){
        tail=head;
        head->value=value;
        head->next=NULL;        
    }else{
        Node *newNode=(Node*)malloc(sizeof(Node));
        newNode->value=value;
        newNode->next=NULL;
        tail->next=newNode;
        tail=newNode;
    }return tail;
}

void output(Node*head){//输出List各节点值
    Node* temp=head;
    for(;temp!=NULL;){
        printf("%d ",temp->value);
        temp=temp->next;
    }printf("\n");
}
Node* fanxu(Node* head){
    if(head->next==NULL){
        return head;
    }else{
        Node *newHead=fanxu(head->next);
        head->next->next=head;
        return newHead;
    }
}
int search1(Node* head){
    Node* temp=head;
    int num=1;
    for(;temp->next!=NULL&&temp->value!=5;num++){
        temp=temp->next;
    }
    if(temp->value==5){
        return num;
    }else return -1;
}
int search2(Node* head){
    int flag=0;
    Node* temp=head;
    int num=1;
    for(;temp->next!=NULL;num++){
        if(temp->value==5){
            flag++;
            if(flag==2){
                return num;
            }
        }temp=temp->next;
    }return -1;
}