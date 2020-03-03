#include<stdio.h>
#define TOT 8
int ans;
void move(int x,int from,int to)
{
	if(x==1) 
	{
		printf("%d to %d\n",from,to);
		ans++;
		return ;
	}
	move(x-1,from,6-from-to);
	printf("%d to %d\n",from,to);
	ans++;
	move(x-1,6-from-to,to);
}
int main()
{
	move(TOT,1,3);
	printf("We will move %d steps",ans);
	return 0;
}
