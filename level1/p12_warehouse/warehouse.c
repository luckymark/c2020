#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAXLEN 10
#define FILENAME "ware.txt"

struct item{ 
    char name[MAXLEN+1];
    unsigned number;
    struct item* next;
};

bool loadList();
bool dumpList();
void showList();
struct item* findItem(char name[]);
bool insertItem(char name[],unsigned number);
bool deleteItem(char name[],unsigned number);
struct item* head=NULL;
void readMe();
inline FILE* fOpen(char * filename,char * mode);

int main(){ 
    loadList();
    readMe();

    unsigned temp;
    char mode,buf[MAXLEN+1];
    while(~scanf("%c",&mode)){ 
        mode=tolower(mode);
        switch(mode){ 
            case 's':
                showList();
                break;
            case 'i':
                scanf("%s %d",buf,&temp);
                insertItem(buf,temp);
                break;
            case 'd':
                scanf("%s %d",buf,&temp);
                deleteItem(buf,temp);
                break;
            case 'q':
            	dumpList();
                return 0;
            default:
                printf(">>>No such mode!\n");
        }
        getchar();
        //可恶的换行符会进入default
    }
    return 0;
}

void showList(){
	printf(">>>Begin\n");
	struct item* now=head;
	while(now){
		if(now->number)
			//number must be greater than zero
			printf("name: %s \t number:%d\n",now->name,now->number);
        now=now->next;
    }
    printf(">>>End\n");
}
bool insertItem(char name[],unsigned number){
    struct item* now=findItem(name);
    if(NULL==now){
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
    printf("The number of %s is %d now!\n",name,now->number);
    return 0;
} 
bool deleteItem(char name[],unsigned number){
    struct item* now=findItem(name);
    if(now==NULL){
        printf(">>>No such item\n");
        return 1;
    }
    if(now->number<number){
        printf(">>>No enough number\n");
        return 1;
    }
    now->number-=number;
    printf("The number of %s is %d now!\n",name,now->number);
    return 0;
}
struct item* findItem(char name[]){
    if(NULL==head){
        return NULL;
    }
    struct item* now=head;
    while(now){
        if(strcmp(name,now->name)==0)return now;
        now=now->next;
    }
    return NULL;
}
bool loadList(){
    system("cls");
    printf(">>>Loading Begin\n");
    FILE *fp=fOpen(FILENAME,"r");
    char name[MAXLEN+1];
    unsigned number;
    while(~fscanf(fp,"%s %d",name,&number)){
        insertItem(name,number);
    }
    fclose(fp);
    printf(">>>Loading End\n");
    return 0;
}
bool dumpList(){
    printf(">>>Dumping Begin\n");
    FILE *fp=fOpen(FILENAME,"w");
    struct item *now=head;
    while(now){
        fprintf(fp,"%s %d\n",now->name,now->number);
        now=now->next;
    }
    fclose(fp);
    printf(">>>Dumping End\n");
    return 0;
}
void readMe(){
    printf("\n>>>>Read Me<<<<\n");
    printf("Usage:\n");
    printf("s : show the warehouse list\n");
    printf("q : dump the list and quit\n");
    printf("i X num : insert num Xs\n");
    printf("d X num : delete num Xs\n\n");
}
inline FILE* fOpen(char * filename,char * mode){ 
    FILE *temp=fopen(filename,mode);
    if(temp)return temp;
    else{ 
        printf("\nFileOpen Error! %s : %s : %d\n",__FILE__,__func__,__LINE__);
        return NULL;
    }
}
