// 我要被这个指针绕晕了 双向链表它不香吗 
// 后来，我用 -> 重构了一遍。 
// 调试了好久QAQ 
#include<stdio.h>

const int maxn = 20;
struct node{
	node* next;
	int value;
	int num;
	node(){
		next = this;
		value = 0;
		num = 0;
	}
	bool isEnd(){
		return next == this;
	}	 
};

struct linkedList{
	node* father;
	int len;
		
	linkedList(int v){	// Be ware that the input was the value of first node
		node* n = new node;
		father = n;
		n->value = v;
		n->num = 1;
		len = 1;
	}
	
	node* findEnd(node *now){
		if(now->isEnd())	return now;
		else return findEnd(now->next);
	}
	
	bool isEnd(node* n){
		return n->isEnd();
	}
	
	void add(int v){
		node* f = findEnd(father);
		node* n = new node;
		n->value = v;
		n->num = f->num+1;
		f->next = n;
		len++;
	}
	
	int _pop(node* n){			// 这里应该定义为Private的，但是不想加戏了。。。 
		if(n->next->isEnd()){
			int value = n->next->value;
			node* next = n->next;
			n->next = n; 
			delete(next);
			return value;
		} 
		return _pop(n->next);
	}
	
	int pop(){
		len--;
		return _pop(father);
	}
	
	node* findNode(node* n, int num){
		if(num == n->num)	return n;
		if(n->next == n)	return NULL;
		return findNode(n->next, num);
	}
	
	int findV(node* n, int v){
		if(n->value == v)	return n->num;
		if(n->next == n)	return -1;
		return findV(n->next, v);
	}
	
	void invert(node* f, node* n){
		bool isEnd = n->isEnd();
		node* next = n->next;
		n->next = f;
		n->num = len - n->num + 1;
		if(isEnd){
			father = n;
			return;
		}
		invert(n, next);
	}
};

void find(linkedList l, int to_find){		// 这里的 find 的逻辑很有趣 
	node* n = l.father;
	while(true){
		int num;
		num = l.findV(n, to_find);
		printf("%d\n", num);
		if(num == -1)	break;
		n = l.findNode(n, num);
		if(n == NULL||n->isEnd())  break;		// 这里可以不用写。。。 
		n = n->next;
	}
}

void invert(linkedList& l){
	
	node* oldf = l.father;
	if(oldf->isEnd())	return;
	l.invert(oldf, oldf->next);
	
	oldf->next = oldf;
	oldf->num = l.len;
}

int main(){
	linkedList l = linkedList(1);
	for(int i = 2; i <= 7; i++)
		l.add(i);
	printf("test pop %d\n", l.pop());
	l.add(5);
	printf("first found: \n");
	find(l, 5);
	invert(l);
	printf("second found: %d\n");
	find(l, 5);
	return 0;
}  
