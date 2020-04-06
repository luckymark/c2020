// 需求实现：文件保存，读取和修改 
// .house 文件格式： # -- 新的一件东西，! -- 结束 


#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string> 
#include "warelist.h"
using namespace std;

const int EXIT = 0, INPORT = 1, EXPORT = 2, SHOWLIST = 3, DEL = 4, CMDBEGIN = '0', CMDEND = '4', maxn = 1000;
FILE * getFile(bool recover);
void saveList(wareList warelist, FILE *f);


int showCommandList(){
	/*
		Clean and show the List, get input, return command
	*/
	
	system("CLS");
	printf("0 -- EXIT\n1 -- INPORT\n2 -- EXPORT\n3 -- SHOWLIST\n4 -- DELETE LIST\n");
	char g;
	while(g = getch()){
		if(g >= CMDBEGIN && g <= CMDEND) break;
	}
	
	return g-'0';
	
}


void inport(){
	 
	char name[maxs], type[maxs];
	int num;
	float price;
	
	printf("请输入商品名\n");
	scanf("%s", name);
	printf("请输入型号\n");
	scanf("%s", type);
	printf("请输入增加数量\n");
	scanf("%d", &num);
	printf("请输入价格\n");
	scanf("%f", &price);
	
	wareList* warelist = makeList(getFile(false));
	if(warelist != NULL)
		warelist->addWare(name, type, num, price);
	else 
		warelist = new wareList(name, type,num, price);
 	saveList(*warelist, getFile(true)); 	
 	
 	delete(warelist);
}


void saveList(wareList warelist, FILE* f){
	ware* now = warelist.father;
	 
	while(warelist.len){
		fprintf(f, "#%s %s %f %d\n", now->name.c_str(), now->type.c_str(), now->price, now->num);
		if(now->isEnd())	break;
		now = now->next;
	}
	fprintf(f, "!");
	fclose(f);
}


void printList(wareList* warelist){
	system("CLS");
	printf("名称			种类			价格			数量\n");
	
	if(warelist == NULL){
		printf("可怜的娃，添一点东西吧（这个程序其实也可以添加负的值喔）\n"); 
		return;
	}
		
	ware* now = warelist->father;
	int len  = warelist->len;
	while(len--){
		printf("%s			%s			%.1f￥			%d\n",
			   now->name.c_str(), now->type.c_str(), now->price, now->num);
		now = now->next;
	}
}


void outport(){
	
	char name[maxs], type[maxs];
	int num;
	float price;
	
	printf("请输入商品名\n");
	scanf("%s", name);
	printf("请输入型号\n");
	scanf("%s", type);
	printf("请输入减少数量\n");
	scanf("%d", &num);
	printf("请输入价格（为了防止不同价格的同类混入QAQ）\n");
	scanf("%f", &price);
	
	wareList* warelist = makeList(getFile(false));
	if(warelist != NULL)
		warelist->addWare(name, type, -num, price);
	else
		warelist = new wareList(name, type, -num, price);	
 	saveList(*warelist, getFile(true));
	delete(warelist);  	
}


void deleteList(){
	
	int res = remove("warehouse.house");
	printf("已删除，按任意键返回主菜单\n");
	getch();
}


void showWareList(){
	printList(makeList(getFile(false)));
	
	printf("按任意键回到主菜单...");
	getch();
}


void listLoop(){
	
	int command = showCommandList();
	switch(command){
		case 0: return;
		case 1: inport(); break;
		case 2: outport(); break;
		case 3: showWareList(); break;
		case 4: deleteList();break;
		default: break;
	}
	listLoop();	
	
}


FILE* getFile(bool recover){
	/*
		WARNING: 这个函数里没有 flose()!!!!!! 
	*/ 
	FILE* wareHouse = fopen("wareHouse.house", "r");
	if(wareHouse == NULL){
		wareHouse = fopen("wareHouse.house", "w+");
		printf("已新建文件，按任意键继续...");
		getch();
	}
	else if(recover){
		fclose(wareHouse);
		wareHouse = fopen("wareHouse.house","w+");
	}
	return wareHouse;	
	
}


int main(){
	
	listLoop();
	printf("已退出\n");
	getch();
	return 0;
	
} 
