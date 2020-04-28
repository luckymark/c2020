#include<stdio.h>
#include<stdlib.h>
#define maxn 6
void Print (int n , char one, char three)
{
	printf_s("%d %c -> %c\n", n, one, three);
	return;
}
void Move(int n, char one, char two,char three)
{
	if (n==1)
	{
		Print(1, one, three);
		return;
	}
	Move(n - 1, one, three, two);
	Print(n, one, three);
	Move(n - 1, two, one, three);
	//ตÝน้

}
int main()
{
	Move(maxn, 'A', 'B', 'C');

}