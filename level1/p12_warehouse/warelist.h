
#ifndef _WARELIST_H_
	#define _WARELIST_H_
#include<string> 

using namespace std;
struct ware{
	
	string name;
	string type;
	int num;
	int price;
	
	ware *next, *last;
	
	ware(char* name, char* type, int num, int price){
		this->name = name;
		this->type = type;
		this->num = num;
		this->price = price;
		this->next = this;
		this->last = this;
	}
	
	bool isEnd(){
		return this == next;
	}
	
	bool isBegin(){
		return this == last;
	}
	
	bool cmp(ware n){
		return (!(name.compare(n.name)))&&(!(type.compare(n.type)))&&(n.price == price);	// 注意下反人性 string.compare 
	}
	 
};


struct wareList{
	
	ware* father;
	ware* end;
	int len;
	
	wareList(char* name, char* type, int num, int price){
		ware* f = new ware(name, type, num, price);
		father  = f;
		end = f;
		len = 1;
	}
	
	ware* _findWare(ware* n, char* name, char* type, int price){
		if(n->name == name && n->type == type && n->price == price)	return n;
		if(n->isEnd()) return NULL;
		return _findWare(n->next, name, type, price);
	}
	
	
	ware* findWare(char* name, char* type, int price){
		return _findWare(father, name, type, price);
	}
	
	
	void addWare(char* name, char* type, int num, int price){
		ware* n = findWare(name, type, price);
		if(n == NULL){
			n = new ware(name, type, num, price);
			end->next = n;
			n->last = end;
			end = n;
			len++;
		}
		else{
			n->num += num;
		}
	}

	void _del(ware* n, int now_num, int want_num){
		if(now_num == want_num){
			len--;
			n->last->next = n->next;
			delete(n); 
		}
		return _del(n->next, now_num+1, want_num);
	}	
	
	void del(int num){
		/*
			没有 pop 了，想 pop 就直接 del(len) 吧 
		*/
		return _del(father, 1, num);
	}
	
};

	//1 根据跟文件路径和模式获取文件指针	<- 这一点我不懂为什么要获取文件路径和指针 
	FILE* getFILE(char* filePath,char* mode);
	//2 使用临时文件替换原文件
	void updateOldFileByNew(char*oldFileName,char*newFileName);
#endif
