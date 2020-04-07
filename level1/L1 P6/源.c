#include<stdio.h>
#include<math.h>
#include<stdbool.h>
void set_prime(int nums[])
{
	int text = 0;
	int i_num = 0;
	for (int i = 2; i < 100; i++) {
		int j;
		for (j = 2; j <= sqrt(i); j++)
			if (i % j == 0)
				text++;
		if (text == 0){
			nums[i_num] = i;
			i_num++;
		}
		text = 0;
	}
}
int main(void)
{
	int primes[30];
	int right = 0;
	bool do_break = false;
	set_prime(primes);
	for (int i = 6; i < 100; i++)
	{	
		for (int prime1 = 0; prime1 < 25; prime1++){
			for (int prime2 = 0; prime2 < 25; prime2++){
				for (int prime3 = 0; prime3 < 25; prime3++){
					if (i == primes[prime1] + primes[prime2] + primes[prime3]){
						right++;
						do_break = right;
						break;
					}
				}
				if (do_break)
					break;
			}
			if (do_break) {
				do_break = false;
				break;
			}
		}
	}
	if (right == 94)
		printf("100ÒÔÄÚÂú×ã");
	return 0;
}