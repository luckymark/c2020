#include <stdio.h>
#include <time.h>
clock_t __cdecl clock(void);
int main(){
	clock_t start, finish;
	double Total_time;
	start = clock();
	int n=2,b;
	int a[1000]={0};
	for(n=2;n<1000;n++){
		if(a[n]==0){
			printf("%d ",n);
		}
		for(b=1;b*n<1000;b++){
			a[b*n]=1;
		}
	}
	finish = clock(); 
	Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("\n%f",Total_time);
	return 0;
}

