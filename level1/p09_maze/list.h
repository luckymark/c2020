//for maze generate
#include<stdio.h>
#include<stdlib.h>
struct node{
    int x;
    int y;
    //position
    struct  node* next;
    //std linked list
};
struct node *head=NULL;
//head ptr
int listSize=0;

void insertList(int x,int y);
void delList(int pos);
void showList();
int getListSize();


void insertList(int x,int y){
	//insert to the head
    struct node* old=head;
    head=(struct node*)malloc(sizeof(struct node));
    head->next=old;
    head->x=x;
    head->y=y;
    ++listSize;
}

void delList(int pos){
    if(pos>listSize || pos<1){
        puts("Error on delele!! Out of Range!!");
        exit(-1);
    }
    struct node *now=head,*temp;
    if(1==pos){
        temp=head;
        head=head->next;
        goto release;
    }
    int i;
    for(i=0;i<pos-2;++i)now=now->next;
    temp=now->next;
    now->next=temp->next;
release:
    free(temp);
    temp=NULL;
    --listSize;
}
void showList(){
    struct node* cursor=head;
    while(cursor){
        printf("x:%d y:%d\n",cursor->x,cursor->y);
        cursor=cursor->next;
        //update
    }
}
inline int getListSize(){ 
    return listSize;
}
