#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


#define LEN_CONSOLE 120     // 控制台长度
#define TIME_INTERVAL 100   // 间隔时间
#define ROUND  2            // 圈数


/* 时间控制器 */
/* 控制时间并更新时间 */
void time_control(time_t* start);

int main()
{
	char arr[] = "abc";
	const int len_arr = strlen(arr);
	time_t start = clock();
	int i = 0;
	int pd = 0;
	int round = -1;
	while (round < ROUND) {
		for (int j = 0; j < i; j++)
			printf(" ");
		printf("%s", arr);
		if (i == LEN_CONSOLE - len_arr)
			pd = 1;
		else if (i == 0) {
			pd = 0;
			round++;
		}

		if (pd == 0)
			i++;
		else
			i--;
		time_control(&start);
		system("cls");
	}
	return 0;
}

void time_control(time_t* start)
{
	time_t now = clock();
	while (now - *start < TIME_INTERVAL)
		now = clock();
	*start = now;
}