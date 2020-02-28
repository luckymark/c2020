#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "func_used.h"
int main()
{
	FILE* fp1, * fp2;
	fopen_s(&fp1, "board&upthing.md", "a+");
	fopen_s(&fp2, "num_step.md", "w");

	if (fp1 == NULL)
		exit(-1);
	else if (fp2 == NULL)
		exit(-2);
	else {
		int num_game = 0; // 关卡数
		int cur_game = 0; // 现在的关卡数
		int count_step = 0;
		int board[LINE][ROW] = { 0 };
		int num_upboard;
		fscanf_s(fp1, "%d", &num_game);
		while (num_game != cur_game) {
			for (int i = 0; i < LINE; i++) {
				for (int j = 0; j < ROW; j++) {
					fscanf_s(fp1, "%d", &board[i][j]);
				}
			}
			fscanf_s(fp1, "%d", &num_upboard);
			Upthing* upboard = (Upthing*)malloc(sizeof(Upthing) * num_upboard);
			for (int i = 0; i < num_upboard; i++) {
				fscanf_s(fp1, "%d%d", &upboard[i].hang, &upboard[i].lie);
			}
			count_step = new_game(num_upboard, board, upboard);
			fprintf(fp1, "%d: %d\n", cur_game + 1, count_step);
			cur_game++;
			free(upboard);	
		}
		fclose(fp1);
		fclose(fp2);
	}
	Sleep(ONE_SECOND);
	return 0;
}


