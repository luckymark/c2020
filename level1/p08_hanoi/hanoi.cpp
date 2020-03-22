#include<stdio.h>

int pillar[3] = {0}, tot = 0;
void show(){
}
void hanoi(int from, int to, int num){
	if(num == 1){
		pillar[from]--;
		pillar[to]++;
		tot++;
		return;
	}
	hanoi(from, 3-from-to, num-1);	// 3-from-to 就是剩下的编号		
	pillar[to]++;
	pillar[from]--;
	tot++;
	hanoi(3-from-to, to, num-1);		
}

int main(){
	scanf("%d", &pillar[0]);
	hanoi(0, 2, pillar[0]);
	
	printf("%d\n", tot);	
	return 0;	
}
