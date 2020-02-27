#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAXLEN 10
//item name length
#define TARGET "ware.txt"
//filename

struct item{ 
    char name[MAXLEN+1];
    unsigned number;
    struct item* next;
};

bool loadList();
bool dumpList();
bool showList();
struct item* findList(char name[]);
//find from list
bool insertList(char name[],unsigned number);
bool delList(char name[],unsigned number);
struct item* head=NULL;
//head ptr
void readMe();
//hint

int main(){ 
    char flag;
    //mode-flag
    char buf[MAXLEN+1];
    //store filename
    unsigned temp;
    loadList();
    readMe();
    while(~scanf("%c",&flag)){ 
        switch(flag){ 
            case 's':
                showList();
                break;
            case 'i':
                scanf("%s %d",buf,&temp);
                insertList(buf,temp);
                break;
            case 'd':
                scanf("%s %d",buf,&temp);
                delList(buf,temp);
                break;
            case 'q':
            	dumpList();
                exit(0);
        }
    }
    return 0;
}


bool showList(){
	printf("--------------Begin\n");
	struct item* now=head;
	while(now){
		if(now->number)
			//number must be greater than zero
			printf("%s %d\n",now->name,now->number);
		now=now->next;
	}
		printf("--------------End\n");
}
bool insertList(char name[],unsigned number){
	struct item* now=findList(name);
	if(now==NULL){
		//new item
		now=(struct item*)malloc(sizeof(struct item));
		now->next=head;
		strcpy(now->name,name);
		now->number=number;
		head=now;
		//insert to the head
	}
	else{
		//old item
		now->number+=number;
	}
	printf("successfully now %s is %d!\n",name,now->number);
	//feedback
} 
bool delList(char name[],unsigned number){
	struct item* now=findList(name);
	if(now==NULL){
		printf("*******No such item\n");
		return 1;
	}
	if(now->number<number){
		printf("*******No enough number\n");
		return 1;
	}
	//error

	now->number-=number;
	printf("successfully now %s is %d!\n",name,now->number);	
	//feedback
}
struct item* findList(char name[]){
	//find node of name's pointer
	if(head==NULL){
		return NULL;
	}
	struct item* now=head;
	while(1){
		if(strcmp(name,now->name)==0)return now;
		//0 means equal
		if(now->next!=NULL)now=now->next;
		else return NULL;
	}
}

bool loadList(){
	system("cls");
	printf("--------------Loading Begin\n");
	FILE *fp=fopen(TARGET,"r");
	char name[MAXLEN+1];
	unsigned number;
	while(~fscanf(fp,"%s %d",name,&number)){
		insertList(name,number);
	}
	fclose(fp);
	printf("--------------Loading End\n");
	return 0;
}
bool dumpList(){
	printf("--------------Dumping Begin\n");
	FILE *fp=fopen(TARGET,"w");
	struct item *now=head;
	while(now){
		fprintf(fp,"%s %d\n",now->name,now->number);
		now=now->next;
	}
	fclose(fp);
	printf("--------------Dumping End\n");
	return 0;
}
void readMe(){
	printf("\n*****Read Me*****\n");
    printf("Usage:\n");
    printf("s : show the warehouse list\n");
    printf("q : dump the list and quit\n");
    printf("i X num : insert num Xs\n");
    printf("d X num : delete num Xs\n");
    printf("*****End******\n");
}