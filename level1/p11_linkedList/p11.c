#include <stdio.h>
#include <stdlib.h>

struct Node{
    int value;
    struct Node* next;
};

static struct Node* Node_head = NULL;

static struct Node* Node_create(int value){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node*));
    newNode->value=value;
    newNode->next=NULL;
    return newNode;
}

static void Node_add(struct Node* newNode){
    struct Node* head=Node_head;
    if(head==NULL){
        Node_head = newNode;
        Node_head->next=NULL;
    }else{
        while (head->next){
            head=head->next;
        }
        head->next=newNode;
        newNode->next=NULL;
    }
}

static void Node_show (){
    struct Node* head=Node_head;
    while(head){
        printf("%d",head->value);
        head = head->next;
    }
    printf("\n");
}

static void Node_reverse(){
    struct Node* head=Node_head;
    int data[50];
    int n=0;
    while (head){
        data[n]=head->value;
        n ++;
        head=head->next;
    }
    head=Node_head;
    while (n){
        n --;
        head->value=data[n];
        head=head->next;
    }
}

static int Node_find(int start,int value){
    struct Node* head=Node_head;
    int count=start;
    while (start){
        start --;
        head=head->next;
    }
    while(head){
        if(head->value==value){
            return count;
        }
        count ++;
        head=head->next;
    }

    return -1;
}

int main(){

    //创建 Node
    Node_head = Node_create(0);

    Node_add(Node_create(1));
    Node_add(Node_create(2));
    Node_add(Node_create(3));
    Node_add(Node_create(4));
    Node_add(Node_create(5));
    Node_add(Node_create(6));
    Node_add(Node_create(7));

    Node_add(Node_create(5));

    //遍历 value
    Node_show();

    //反序
    Node_reverse();
    Node_show();
    Node_reverse();//恢复顺序 便于后续观察

    //把 head 作为 0 序号
    //查找 5
    int count1 = Node_find(0,5);
    printf("%d\n",count1);

    //查找下一个 5
    int count2 = Node_find(count1+1,5);
    printf("%d\n",count2);

    return 0;
}