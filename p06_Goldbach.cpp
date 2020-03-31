#include <stdio.h>
int main(){
	int i=4,a,b,c;
	int prime[100]={0},n=0;
	//prime[0]=2;
	for(a=2;a<100;a++){
		for(b=2;b<a;b++){
			if(a%b==0){
				break;
			}
		}
		if(a==b){
					prime[n++]=a;
			}
	}//找出100以内的素数 
	for(i=4;i<100;i+=2){
		for(a=0;a<n;a++){
			for(b=0;b<n;b++){
				if(prime[a]+prime[b]==i){
					printf("%d+%d=%d\n",prime[a],prime[b],i);
					goto next;
				}
			}
		}
		next:;
	}
	return 0;
}
