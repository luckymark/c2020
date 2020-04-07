#include<stdio.h>
#include<stdlib.h>
struct Node {
	int num;
	struct Node* next;
};

typedef struct Node* Position;
typedef struct Node* List;

List Create();
void Ergodic(List L);
Position Reversal(List L);
int Find(List L, int X,int times);

int main(void)
{
	List list1 = Create();			//创建
	Ergodic(list1);					//遍历
	for (int i = 1; Find(list1, 1, i) != -1; i++)	//查找直到不存在为止
	{
		printf("第%d次 出现在%d", i,Find(list1, 1, i));
	}
	List list2 = Reversal(list1);					//反转节点
	return 0;
}

List Create()
{
	List head, end;
	head = (Position)malloc(sizeof(struct Node));
	head->next = NULL;
	end = head;
	for (int i = 0; i < 10; i++)
	{
		Position pnew = (Position)malloc(sizeof(struct Node));
		pnew->num = i;
		pnew->next = NULL;
		end->next = pnew;
		end = pnew;
	}
	return head;
}

void Ergodic(List L)
{
	Position p = L->next;
	while (p != NULL)
	{
		printf("%d\t", p->num);
		p = p->next;
	}
}

int Find(List L, int X, int times)
{
	int count_time = 0;
	int sn = 0;
	Position p = L->next;
	while (p != NULL)
	{
		if (p->num == X)
		{
			count_time++;
			if (count_time == times)
				break;
		}
		sn++;
		p = p->next;
	}
	if (p == NULL) 
		return -1;
	else 
		return sn;
}

Position Reversal(List L)
{
	Position p = L, tem = L, pre = NULL;
	
	while (tem != NULL)
	{
		p = tem;
		tem = p->next;
		p->next = pre;
		pre = p;
	}
	return p;
}