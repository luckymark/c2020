#include<stdio.h>
#include<math.h>
#define MAX_LENGTH 100001

int main(void)
{
	//declaration and input
	int book[MAX_LENGTH] = {0};
	int a = 0,i = 0,j = 0;
	scanf("%d",&a);
	
	//check input
	if(a >= MAX_LENGTH - 1)
	{
		printf("Out of capacity");
		return 0;
	}
	
	//short circuit
	if(1 == a)
	{
		printf("No");
		return 0;
	}
	if(2 == a || 3 == a)
	{
		printf("Yes");
		return 0;
	}
	
	//create prime list
	book[1] = 1;
	for(i = 1; i<= sqrt(a);i++)
	{
		if(1 == book[i])
			continue;
		j = i * i;
		while(j <= a)
		{
			book[j] = 1;
			j += i;
		}
	}
	
	//output result
	if(1 == book[a])
		printf("No");
	else
		printf("Yes");
		
	return 0;	
} 
