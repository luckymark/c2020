#include<stdio.h>
const int PLETES=3;
void honoi(int now,int to,int pletes)
{
	if(pletes==1) printf("%c->%c\n",'a'+now-1,'a'+to-1);
	else
	{
		int use;
		for(int i=1;i<=3;i++)
		if(i!=now&&i!=to) use=i;
		honoi(now,use,pletes-1);
		printf("%c->%c\n",'a'+now-1,'a'+to-1);
		honoi(use,to,pletes-1);
	}
}
int main()
{
	honoi(1,3,PLETES);
}
