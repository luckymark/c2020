#include <stdio.h>
#include <stdlib.h>
#define LENGTH 8

//global
typedef struct Node
{
    // the head node contains the length of LinkList
    int value;
    struct Node *next;
} Node;
typedef struct Node *LinkList;

//prototype
LinkList GetReversedLinkList(LinkList headNode);
LinkList NewLinkList_WithHeadNode(int length);
int FindIndexByValue(LinkList headNode, int value, int start_index);
LinkList ClearList(LinkList headNode);

int main()
{
    //init
    LinkList a = NewLinkList_WithHeadNode(LENGTH),p = a->next;
    int counter = 1;

    //show value
    while(NULL != p)
    {
        printf("the value of Node %d is %d \n",counter,p->value);
        p = p->next;
        counter++;
    }

    //reverse
    a = GetReversedLinkList(a);

    //find first 5
    int indexOf5 = FindIndexByValue(a,5,0);
    printf("The index of first node with value 5 is %d \n",indexOf5);

    //find second 5
    indexOf5 =  FindIndexByValue(a,5,indexOf5 + 1);
    printf("The index of second node with value 5 is %d \n",indexOf5);

    //delete linked list
    a = ClearList(a);

    return 0;
}

LinkList ClearList(LinkList headNode)
{
    LinkList p = headNode,q = p->next;
    while(p != NULL)
    {
        q = q->next;
        free(p);
        p = q;
    }

    return NULL;
}

int FindIndexByValue(LinkList headNode, int value, int start_index)
{
    int result = -1;
    LinkList p = headNode->next;

    while (p != NULL)
    {
        if(value != p->value || result + 2 < start_index)
        {
            p = p->next;
            result++;
            continue;
        }
        break;
    }
    result += 2;

    return result;
}

LinkList NewLinkList_WithHeadNode(int length)
{
    //create head node
    LinkList head_node = (LinkList)malloc(sizeof(Node)),p = NULL,r = NULL;
    head_node->value = 0;
    head_node->next = NULL;
    r = head_node;

    //add nodes
    int i;
    for(i = 0;i<length;i++)
    {
        //create new node
        p = (LinkList)malloc(sizeof(Node));
        p->value = 0;

        // TODO WARNING: specific requirement for test, delete before using
        {if(2 == i || 4 == i)
            p->value = 5;}

        //add to tail
        r->next = p;
        r = p;
    }
    r->next = NULL;

    return head_node;
}

LinkList GetReversedLinkList(LinkList headNode)
{
    //init
    LinkList current_p = NULL,backup_p = NULL,pioneer_p = NULL;

    //reverse
    current_p = headNode->next;
    pioneer_p = current_p;
    headNode->next = NULL;
    while(current_p != NULL)
    {
        pioneer_p = pioneer_p->next;
        current_p->next = backup_p;
        backup_p = current_p;
        current_p = pioneer_p;
    }
    headNode->next = backup_p;

    return headNode;
}
