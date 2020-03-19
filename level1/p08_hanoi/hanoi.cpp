#include<cstdio> 
#include<iostream>
using namespace std;
const int N=3;
int step=0; 
void move(char from,char to)
{
	printf("step %d: %c -> %c\n",++step,from,to);
}
void hanoi(int n,char now,char target,char mid)
{
	if(n==1)
	{
		move(now,target);
		return;
	}
	hanoi(n-1,now,mid,target);
	move(now,target);
	hanoi(n-1,mid,target,now);
}
/*
将now柱子上的除最下面圆盘的n-1个圆盘借助target柱子，移到mid柱子上 
然后将now柱子上剩下的最下面的圆盘移动到target柱子上 
最后将mid柱子上的n-1个圆盘移动到target柱子上 
如果n==1，即只需要把盘子从now柱子移动到target上 
*/ 
int main()
{
	hanoi(N,'1','3','2');
	return 0;
}
