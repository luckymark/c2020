//copy 一下上道题的线性筛做个素数表 
#include<stdio.h>
#include<cstring>
const int maxn = 100 + 5;
bool not_prime[maxn];		//可怕的双重否定 
int prime[maxn/2], top = 0;	//其实这里该用欧拉函数定义，狗头 
int main(){
	memset(not_prime, 0, sizeof(not_prime));
	for(int i = 2;i <= maxn - 5; i++){
		if(!not_prime[i]){		//是素数 
//			printf("%d\n", i);
			prime[++top] = i;
		}
		
		for(int j = 1; j <= top && i*prime[j] <= maxn-5; j++){
			not_prime[i*prime[j]] = true;
			if(i % prime[j] == 0)	//可以整除的话
				break; 
		}
		
	}
//	开始模拟吧 
	for(int i = 6; i <= 100; i++){			//从5开始 
		int yes = false;
		for(int j = 1; j <= top; j++)
			for(int k = j; k <= top; k++)
				for(int l = k; l <= top; l++)
					if(prime[j]+prime[k]+prime[l] == i){
						yes = true;
						printf("%d=%d+%d+%d\n", i, prime[j], prime[k], prime[l]);
					}
		if(!yes)	printf("我找到了不符合哥德巴赫猜想的数，狗头\n");
	}
	 
} 
