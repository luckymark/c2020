#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define For(x,a,b) for(x=a;x<=b;x++)
int i,i1,i2;
int main(void)
{
	double age;
	for(age=0;age<1000;age++)
	if((age/12+age/6+age/7+5+age/2+4)==age){
	printf("age=%.0f\n",age-4);
	break;
	}
	system("pause");
	return 0;
}
