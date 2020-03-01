#include<stdio.h>
#include<math.h>
#include<time.h>

#define LENGTH 1000

void elapsed_time(void);

int main(void)
{
	//declaration and input
	int book[LENGTH + 1] = {0};
	int i = 0,j = 0;
	
	//create prime list
	book[1] = 1;
	for(i = 1; i<= sqrt(LENGTH);i++)
	{
		if(1 == book[i])
			continue;
		j = i * i;
		while(j <= LENGTH)
		{
			book[j] = 1;
			j += i;
		}
	}
	
	//output result
	for(i = 1;i<= LENGTH;i++)
		if(0 == book[i])
			printf("%d\n",i);
	
	elapsed_time();
	getchar();
	return 0;	
}

void elapsed_time()
{
	printf("Elapsed time:%u ms.\n",clock());
}
