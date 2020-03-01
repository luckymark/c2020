#include<stdio.h>
#define maxn 20
void move(int deep,int st,int ed)
{
	if(deep==1)
	{
		printf("%d->%d\n",st,ed);
		return;
	}
	int mid=6-st-ed;
	move(deep-1,st,mid);
	move(1,st,ed);
	move(deep-1,mid,ed);
}
int main()
{
	int n;
	scanf("%d",&n);
	move(n,1,3);
} 
