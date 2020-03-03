//这个就要用到不会写的线性筛了 
#include<stdio.h>
#include<cstring>

const int maxn = 1000 + 5;
bool not_prime[maxn];		//可怕的双重否定 
int prime[maxn/2], top = 0;	//其实这里该用欧拉函数定义，狗头 
int main(){
	memset(not_prime, 0, sizeof(not_prime));
	for(int i = 2;i <= maxn - 5; i++){
		if(!not_prime[i]){		//是素数 
			printf("%d\n", i);
			prime[++top] = i;
		}
		
		for(int j = 1; j <= top && i*prime[j] <= maxn-5; j++){
			not_prime[i*prime[j]] = true;
			if(i % prime[j] == 0)	//可以整除的话
				break; 
		}
		
	}
	printf("线性筛，复杂度接近O(n)\n");
	return 0;
} 
