// 需求实现：文件保存，读取和修改 
// .house 文件格式： # -- 新的一件东西，! -- 结束 
// 用链表吗QAQ，还是用吧QAQ 
// 这次链表有经验了啊，改进了一下，用了双向，以及那个 end 指针我为啥上一道题没有想到QAQ
// 我睡了个午觉起来想用 vector 了。。。 可是都写了一半了，哭瞎 
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include "warelist.h"
using namespace std;

const int EXIT = 0, INPORT = 1, EXPORT = 2, SHOWLIST = 3, maxs = 1024, maxn = 1000;
FILE * getFile(bool recover);
void saveList(wareList warelist, FILE *f);

//下次的类名第一个一定大写，这次真的不想改了 


int showList(){
	/*
		Clean and show the List, get input, return command
	*/
	
	system("CLS");
	printf("0 -- EXIT\n1 -- INPORT\n2 -- EXPORT\n3 -- SHOWLIST\n");
	char g;
	while(g = getch()){
		if(g >= '0' && g <= '3') break;
	}
	
	return g-'0';
	
}


wareList makeList(FILE* wareHouse){
	
	wareList* list = NULL;
	char u = getchar();
	while(u != '!' && u != EOF){
		if(u == '#'){
			char name[maxs], type[maxs];
			int num, price;
			scanf("%s%s%d%d", name, type, &num, &price);
			
			if(list == NULL)
				list = new wareList(name, type, num, price);
			else list->addWare(name, type, num, price);
		}
		u = getchar();
	}
	fclose(wareHouse);
	delete(list);
} 


void inport(){
	 
	char name[maxs], type[maxs];
	int num, price;
	
	printf("请输入商品名\n");
	scanf("%s", name);
	printf("请输入型号\n");
	scanf("%s", type);
	printf("请输入增加数量\n");
	scanf("%d", &num);
	printf("请输入价格\n");
	scanf("%d", &price);
	
	wareList warelist = makeList(getFile(false));
	warelist.addWare(name, type, num, price);
 	saveList(warelist, getFile(true)); 	
 	
}


void saveList(wareList warelist, FILE* f){
	ware* now = warelist.father;
	 
	while(warelist.len){
		printf("#%s %s %d %d\n", now->name, now->type, now->price, now->num);
		if(now->isEnd())	break;
		now = now->next;
	}
	printf("!");
	fclose(f);
}


void printList(wareList warelist){
	ware* now = warelist.father;
	int len  = warelist.len;
	while(len--){
		printf("%s	%s	%d	%d￥\n", now->name, now->type, now->price, now->num)
	}
}


void outport(){
	
	char name[maxs], type[maxs];
	int num, price;
	
	printf("请输入商品名\n");
	scanf("%s", name);
	printf("请输入型号\n");
	scanf("%s", type);
	printf("请输入减少数量\n");
	scanf("%d", &num);
	pritf("请输入价格（为了防止不同价格的同类混入QAQ）\n");
	scanf("%d", &price);
	
	wareList warelist = makeList(getFile(false));
	warelist.addWare(name, type, -num, price);
 	saveList(wareList, getFile(true));
	  	
}


void showWareList(){
	printList(makeList(getFile(false)));
}


void LISTLOOP(){
	
	int command = showCommandList();
	switch(command):
		case 0: return;
		case 1: inport(); break;
		case 2: outport(); break;
		case 3: showWareList(); break;
		default: break;
		
	LISTLOOP();	
	
}


FILE* getFile(bool recover){
	
	FILE* wareHouse = fopen("wareHouse.house", "r+");
	if(wareHouse == NULL){
		wareHouse = fopen("wareHouse.house", "w+");
		printf("已新建文件，按任意键继续...")
		getch();
	}
	else if(recover){
		fclose(wareHouse);
		wareHouse = fopen("wareHouse.house","w+");
	}
	return wareHouse;	
	
}


int main(){
	
	Listloop();
	printf("已退出\n");
	getch();
	return 0;
	
} 
