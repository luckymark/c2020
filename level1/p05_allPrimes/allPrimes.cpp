#include<stdio.h>
#include<math.h>
#include<time.h> 
#include<stdlib.h>
#include<windows.h>

const int MAX=1002;

bool jud[MAX];
int prime[MAX];
 
int main()
{
	DWORD start=GetTickCount();
	int tol=0;
	for(int i=2;i<=MAX;i++)
	{
		if(jud[i]==0) prime[++tol] = i;
		for(int j=1; j<=tol; j++)
		{
			if(prime[j]*i > MAX) break;
			jud[prime[j]*i]=1;
			if(i%prime[j]==0) break; 
		}
	}
	for(int i=2;i<=1000;i++)
	if(jud[i]==0) printf("%d\n",i);
	DWORD end=GetTickCount();
	//Sleep(1000);
	printf("the total time cost is %d ms",end-start);

} 
