#include <stdio.h>
int main(){
	int n,a;
	scanf("%d",&n);
	for(a=2;a<n;a++){
		if(n%a==0){
			break;
		}
	}
	if(a==n){
		printf("%d is prime",n);
	}else{
		printf("%d is not 12prime",n);
	}
	return 0;
} 
