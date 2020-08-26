#include <stdio.h>
#include <stdlib.h>
int j=1;
typedef struct link{
    int data;
    int num;
    struct link*next;
    struct link*pre;
}Link;
Link *Appendnode(Link*head){
    int data;
    Link*p=NULL;
    Link*pr=head;
    p=(Link*)malloc(sizeof(Link));
    if(NULL==p){
        printf("error:no memery");
        exit(0);
    }
    if(NULL==head){
        head=p;
    }else{
        while(pr->next!=NULL){
            pr=pr->next;
        }
        pr->next=p;
    }
    scanf("%d",&data);
    p->data=data;
    p->next=NULL;
    p->pre=pr;
    p->num=j++;
    return head;
}
void Displaynode(Link*head){
    Link*p=head;
    int cnt=0;
//    else {
//        while(p->next!=NULL){
//            p=p->next;
//            cnt++;
//        }
//        while(cnt>=0){
//            printf("%d %d ",p->num,p->data);
//            cnt--;
//            p=p->pre;
//        }
//    }
    if(head==NULL){
        return;
    }
    else {
        while(p!=NULL){
        printf("%d %d ",p->num,p->data);
        p=p->next;
        }
    }
}
void Deletenode(Link*head,int num){
    Link*pf,*p;
    p=head;
    if(head==NULL){
        puts("a empty link");
    }
    while(p->num!=num&&p->next!=NULL){
        pf=p;
        p=p->next;
    }
    if(p->num==num){
        if(p==head){
            head=p->next;
        }
        else{
            pf->next=p->next;
            free(p);
            for (int h = pf->next->num; h < j; h++) {
                pf=pf->next;
                pf->num-=1;
            }
        }
    }
    else{
        puts("can't find node");
    }
}
int Findnode(Link*head,int data,int num){
    Link*p=head;
    while(--num){
        p=p->next;
    }
    do{
        p=p->next;
        if(NULL==p)
        {
            return -1;
        }
    }
    while(p->data!=data);
    return p->num;
}
void Insertnode(Link*head,int num){
    int data,cnt;
    cnt=num;
    Link*p=head;
    Link*pf,*new;
    Link*pb=head;
    while(--cnt){
        pb=pf=p;
        p=p->next;
    }
    new=(Link*)malloc(sizeof(Link));
    scanf("%d",&data);
    new->data=data;
    new->num=num;
    new->next=p;
    pf->next=new;
    pb=pb->next;
    for(int c=num;c<j;++c){
        pb=pb->next;
        pb->num+=1;
    }
}
Link* Reverselink(Link*head){
    int cnt=0;
    if(head==NULL){
        return NULL;
    }
    else {
    Link*ex;
    Link*p;
    Link*newhead;
    p=head;
    while(p->next!=NULL){
        ex=p->next;
        p->next=p->pre;
        p->pre=ex;
        p=p->pre;
        cnt++;
    }
    int n=cnt+1;
    ex=p->next;
    p->next=p->pre;
    p->pre=ex;
    newhead=p;
    while(cnt>0){
        p->num=n-cnt;
        p=p->next;
        cnt--;
    }
    p->num=n;
    return newhead;
    }

}
int main() {
    Link*head=NULL;
    int cnt;
    int n=0;
    int*p;
    puts("the length of the link is ");
    scanf("%d",&cnt);
    p=(int*)malloc(cnt* sizeof(int));
    *p=1;
    for(int u=0;u<cnt;u++) {
        head = Appendnode(head);
    }
//    Insertnode(head,2);
    head=Reverselink(head);
    while(cnt--){
        *(p+n+1)=Findnode(head,5,*(p+n));
        if(*(p+n)!=-1){
            n++;
        }else break;
    }
    Displaynode(head);
    return 0;
}