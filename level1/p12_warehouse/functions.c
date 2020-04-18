//
// Created by 20694 on 2020/4/16.
//
#include "warehouse.h"
extern int modenum;
extern int i;
extern store sto;
extern int cnt;
extern FILE*in;
extern FILE*out;
extern int flag;
static int number;
static char model[30];
int x=1;
store* read(store*head){
    fscanf(in,"we have %d kinds of modes",&modenum);
    if(modenum==0){
        modenum+=1;
    }
    while(modenum--){
        head=appendnode(head);
        cnt++;
    }
    return head;
}
store*appendnode(store*head){
    store*p=NULL;
    store*pr=head;
    int num;
    char modes[30];
    p=(store*)malloc(sizeof(store));
    assert(NULL!=p);
    if(NULL==head){
        head=p;
        fscanf(in,"%s %d",p->model,&p->num);
        p->next=NULL;
        return head;
    }else{
        while(pr->next!=NULL){
            pr=pr->next;
        }
        pr->next=p;
        fscanf(in,"%s %d",p->model,&p->num);
        p->next=NULL;
        return head;
    }
}
void write(store*head){
    fprintf(out,"we have %d kinds of modes\n",cnt);
    store*p=head;
    while(cnt--){
        fprintf(out,"%s %d\n",p->model,p->num);
        p=p->next;
    }
}
store *Deletenode(store*head,int y){
    store*pf,*p;
    p=head;
    pf=NULL;
    while(y--){
        pf=p;
        p=p->next;
    }
    if(p==head){
        head=p->next;
        free(p);
        return head;
    }
    else{
    pf->next=p->next;
    free(p);
    }
    return head;
}
void Displaynode(store *head){
    store*p=head;
    if(head==NULL){
        return;
    }
    else {
        while(p!=NULL){
            printf("%s %d ",p->model,p->num);
            p=p->next;
        }
    }
}
store* choose(int cho,store*head) {
    store *p=head;
    switch (cho) {
        case 1:
            Displaynode(head);
            break;
        case 2:
            scanf("%s %d", model, &number);
//            int length=strlen(model);
            while(T){
                if(0==strncmp(p->model,model,strlen(model))){
                    p->num+=number;
                    return head;
                } else{
                    if(p->next!=NULL) {
                        p = p->next;
                    }else{
                        return head;
                    }
                }
            }
        case 3:
            scanf("%s %d", model, &number);
            while(T){
                if(0==strncmp(p->model,model,strlen(model))){
                    p->num-=number;
                    if(p->num<=0){
                        head=Deletenode(head,x-1);
                        cnt--;
                    }
                    return head;
                } else{
                    if(p->next!=NULL) {
                        p = p->next;
                        x+=1;
                    }else{
                        return head;
                    }
                }
            }
        default:
            return head;
            }
    }

