#include <stdio.h>
#include <string.h>
#include<math.h>

int isprime(int num)
{
    if(num<=3)  return num>1;
    if(num % 6 != 1 && num % 6 != 5)  return 0;
    else
    {
        int i;
        int sqr=ceil(sqrt(num));
        for(i=5;i<=sqr;i+=6)
        {
        	if(num%i==0)  return 0;
		}
            
        return 1;
    }
}
int main() {
	int num; 
	printf("Please input a postive integer£º");
    scanf("%d",&num);
    if(isprime(num))
    {
    	printf("It's a prime");
	}
        
    else  
	{
		printf("It's a not prime");
	}
    return 0;
}

