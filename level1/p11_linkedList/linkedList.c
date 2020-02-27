#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

struct node{
	//std linked list
    int value;
    struct  node* next;
};
struct node *head=NULL;
//head ptr

void reverseList(struct node *now,struct node *before);
//recursively reverse

struct node* findEnd();
//would like to insert node to the end,every time

void insertList(int target);
//insert node

int findNext(int target);
//find node of target

void showList();

int tempvalue,i;
//temp
int main() {
    int num;
    puts("Please input the number of elements");
    scanf("%d",&num);
    puts("Pleae input elements:");
	for(i=0;i<num;++i){
        scanf("%d",&tempvalue);
        insertList(tempvalue);
    }
    //make list

    printf("\nIn order:\n");
    showList();
    //show in order

    printf("\n\nFind 5 firstly:\n");
    printf("%d",findNext(5));
    //find 5
    printf("\nFind 5 secondly:\n");
    printf("%d\n",findNext(5));
    //find 5

    reverseList(head,NULL);
    printf("\nReverse:\n");
    showList();
    //show reversed list
    return 0;
}
void reverseList(struct node *now,struct node *before){
    if(now->next==NULL){
    	//change the end into head
        head=now;
        return;
    }
    reverseList(now->next,now);
    //reverse the part behind now
    now->next->next=now;
    now->next=before;
    //reverse now
}
void insertList(int value){
	//insert to the end 
    struct node* now=findEnd(head);
    if(now==NULL){
    	//empty list
        head=(struct node*)malloc(sizeof(struct node));
        head->value=value;
        head->next=NULL;
        return;
    }
    now->next=(struct node*)malloc(sizeof(struct node));
    now->next->value=value;
    now->next->next=NULL;
}
struct node* findEnd(){
    struct node * now=head;
    if(now==NULL)return NULL;
    while(now->next)now=now->next;
    return now;
}
void showList(){
    struct node* now =head;
    while(now){
        printf("%d ",now->value);
        now=now->next;
        //renew
    }
}
int findNext(int target){
    //find target number
    if(head==NULL)return -1;
    static int ptr=0;
    //save old moves
    struct node* now=head;
    for(i=1;i<ptr+1;++i)now=now->next;
   	//repeat old moves
    while(now){
        ptr++;
        if(now->value==target){
            return ptr;
        }
        now=now->next;
    }
    return -1;
}
