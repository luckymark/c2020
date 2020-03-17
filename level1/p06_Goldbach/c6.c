#include<stdio.h>
#include<math.h>
#define LENGTH 100
int isGdbhArith(int number);
int isPrimer(int number);
int main() {
	for (int i = 4; i <= LENGTH; i += 2)isGdbhArith(i);
	return 0; 
}
int isGdbhArith(int number){
		for (int i = 2; i<=number/2; i++)
		{
			if (isPrimer(i)==1 && isPrimer(number - i)==1)
			{
				printf("%d = %d + %d\n", number, i, number - i);
				return 1;
			}
		}
		return 0;
}
int isPrimer(int number) {
	if (number == 2 || number == 3)  return 1;
	for (int i = 2; i * i <= number; i++)
	{
		if (number % i == 0) return 0;
	}return 1;
}
