#include<stdio.h>
int main()
{
	int fatherAge,sonAge;
	for(fatherAge=1;;fatherAge++)
	{
		if(fatherAge%12!=0 || fatherAge%7!=0) continue;
		sonAge=fatherAge-fatherAge/6-fatherAge/12-fatherAge/7-5-4;
		if(sonAge==fatherAge/2)
		{
			printf("He is %d when his son died.",fatherAge-4);
			break;
		}
	}
	return 0;
}
