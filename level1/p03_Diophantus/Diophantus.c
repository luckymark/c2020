#include<stdio.h>
int main()
{
	int dad,son;
	int a,b;
	for(dad=12;1;dad=dad+12){
		if(dad%7==0){
			son=dad/2;
			a=dad-4-5-(dad/6)-(dad/12)-(dad/7);
			if(son==a){
				b=dad-4;
				printf("¶ù×ÓËÀÊ±¶ª·¬Í¼%dËê",b);
				break;
			}
		}
	}
	return 0;
}
