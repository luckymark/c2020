#include <stdio.h>
void a(int num);
int main()
{
	int i;
	
	for(i=4;i<=100;i+=2)
	{
		a(i);
	}
	return 0;
}

void a(int num)
{
	int b,j,z,q;
	int panduan_1=0,panduan_2=0;
	printf("\n");
		for(j=2;j<=num/2;++j)
		{
			for(z=2;z<j/2;++z)
			{
				if(j%z==0)
				{
					panduan_1++;
					break;
				}
			}
			if(panduan_1==0)
			{
				b=num-j;
				for(q=2;q<b/2;++q)
				{
					if(b%q==0)
					{
						panduan_2++;
						break;
					}
				}
				if(panduan_2==0)
				{
					printf("%d = %d +%d\n",num,j,b); 
				}
			}
			panduan_1=0;
			panduan_2=0;
		}	
}
