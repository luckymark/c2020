#include"warehouse.h"
struct item* head=NULL;

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
    if(NULL==now){
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
        if(0==strcmp(name,now->name))return now;
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
