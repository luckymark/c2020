#include<stdio.h>
#include<math.h>
int main(void) {
	int num;
	int text = 0;
	printf("Put a num, 'q' to quit\n");
	while (scanf_s("%d", &num)) {
		for (int i = 2; i <= sqrt(num); i++)
			if (num % i == 0)
				text++;
		if(text != 0)
			printf("%d is not prime\n", num);
		else
			printf("%d is prime\n", num);
		text = 0;
	}
	return 0;
}