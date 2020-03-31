#include<stdio.h>
#include <stdlib.h>
#define NUM 10


typedef struct LinkList{
    int data;
    struct LinkList * NextNode;
}Link_list;

Link_list *CreateNode(int n);

void TravelLIst(Link_list * List_ptr);

Link_list * ReverseLinklist(Link_list *Op_ptr);

int SearchLinkList(Link_list *Op_ptr, int F_num, int count);

int main()
{
    int ReValue;
    Link_list * HeadNode = (Link_list*)malloc(sizeof(Link_list));
    HeadNode->data = NUM;
    HeadNode->NextNode = CreateNode(NUM);
    TravelLIst(HeadNode);
    HeadNode = ReverseLinklist(HeadNode);
    ReValue = SearchLinkList(HeadNode, 5, 1);
    printf("%d\t", ReValue);
    ReValue = SearchLinkList(HeadNode, 5, 2);
    printf("%d", ReValue);
    return 0;
}

Link_list *CreateNode(int n){
    int i;
    Link_list * temp = NULL;
    for (i = 0; i < n; i++){
        Link_list * Node = (Link_list*)malloc(sizeof(Link_list));
        Node->NextNode = temp;
        Node->data = 10-i;
        temp = Node;
    }
    return temp;
}

void TravelLIst(Link_list * List_ptr){
    int i = 0;
    if (List_ptr == NULL)
        exit(0);
    printf("please choose a action: \n1.Node infomation\n2.change Node infomaton\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        while (List_ptr != NULL) {
            printf("Node %d is %d\n", i++, List_ptr->data);
            List_ptr = List_ptr->NextNode;
        }
    }
    else if (choice == 2)
    {
        i = 0;
        while (List_ptr != NULL)
        {
            printf("Node %d change to :\n", i++);
            scanf("%d",&List_ptr->data);
            List_ptr = List_ptr->NextNode;
        }
    }
}

Link_list * ReverseLinklist(Link_list *Op_ptr) {
    Link_list *temp1 = Op_ptr;
    Link_list *temp2 = Op_ptr->NextNode;
     do {
        Op_ptr->NextNode = Op_ptr->NextNode->NextNode;
        temp2->NextNode = temp1;
        temp1 = temp2;
        temp2 = Op_ptr->NextNode;
        if(temp2->NextNode == NULL) {
            temp2->NextNode = temp1;
            Op_ptr->NextNode = NULL;
            break;
        }
    }while (1);
    return temp2;
}

int SearchLinkList(Link_list *Op_ptr, int F_num, int count){
    int i = 0;
    int Index = 0;
    while (Op_ptr->NextNode != NULL){
        if (Op_ptr->data == F_num){
            Index++;
            if (Index == count)
            {
                return i;
            }
        }
        Op_ptr = Op_ptr->NextNode;
        i++;
    }
    if (Index < count)
    {
        return -1;
    }
}