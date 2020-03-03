#include<stdio.h>
#include<math.h>

int main(){
	int n;
	scanf("%d",&n);
	if(n <= 0){
		printf("不是正整数\n");
		return 0;
	}
	
	bool is_prime = true;
	for(int i = 2; i <= sqrt(n); i++){
		if(!(n % i)){
			is_prime = false;
			break;
		}
	}
	if(is_prime && n != 1)	printf("是质数\n");
	else printf("不是质数\n");
	return 0;
} 
