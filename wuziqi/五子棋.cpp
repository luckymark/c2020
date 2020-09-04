#include <graphics.h>
#include <conio.h>
#include <stdio.h>

#define MAX 2147483647	
#define MIN -2147483648
#define DEPTH 4

int player = 0;
int board[16][16] = { 0 };
int x, y;
int fenshu[6] = { 0,0,10,100,1000,10000 };
int derication[4][2] = { {1,0},{0,1},{1,1},{-1,1} };

void begin();
void chess();
void playerturn();
void AIturn();
int judge(int a, int b, int board_[16][16]);
int score(int board_[16][16]);
int end(int a, int b, int board_[16][16]);
int score_1(int a, int board_[16][16]);
int score_2(int a, int board_[16][16]);
int MaxMin(int deep, int board_[16][16]);


int main()
{
	begin();
	RECT r = { 125, 400, 275, 425 };
	while (TRUE)
	{
		if (player > 0)
		{
			drawtext(_T(" your turn "), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			playerturn();
		}
		else
		{
			drawtext(_T(" AI's turn "), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			AIturn();
		}

		for (int i = 1; i <= 15; i++)
		{
			for (int j = 1; j <= 15; j++)
				printf("%d ", board[i][j]);
			printf("\n");
		}
		//printf("%d,%d,%d,%d\n", x, y, end(x, y, board), score(board));

		if (end(x, y, board))
			break;
		player *= -1;
	}
	if (player > 0)
	{
		setcolor(RED);
		drawtext(_T("   YOU WIN !  "), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		setcolor(GREEN);
		drawtext(_T("   YOU LOSE !  "), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	getchar();
}


void begin()
{
	initgraph(400, 450, EW_SHOWCONSOLE);
	setbkcolor(WHITE);
	cleardevice();
	setcolor(BLACK);
	for (int i = 25; i <= 375; i += 25)
	{
		line(25, i, 375, i);
		line(i, 25, i, 375);
	}

	POINT pts[] = { {125, 400}, {275, 400}, {275, 425},{125, 425} };
	fillpolygon(pts, 4);
	RECT r = { 125, 400, 275, 425 };
	drawtext(_T("Play Now"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_LBUTTONDOWN:
			if (125 <= m.x && m.x <= 275 && m.y >= 400 && m.y <= 425)
				player = 1;
			break;
		default: break;
		}
		if (player != 0)
			break;
	}
}


void playerturn()
{
	int chessif = 0;
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (17 <= m.x && m.x < 383 && m.y >= 17 && m.y < 383 && ((int)m.x % 25 <= 8 || (int)m.x % 25 >= 17) && ((int)m.y % 25 <= 8 || (int)m.y % 25 >= 17) && board[(int)((m.y + 10) / 25)][(int)((m.x + 10) / 25)] == 0)
			{
				x = (int)((m.y + 10) / 25);
				y = (int)((m.x + 10) / 25);
				board[x][y] = 1;
				chess();
				chessif = 1;
			}
		}
		if (chessif == 1)
		{
			return;
		}

	}
}


void AIturn()
{
	MaxMin(DEPTH, board);
	board[x][y] = 2;
	chess();
}


void chess()
{
	if (player == 1)
	{
		setcolor(BLACK);
		setfillcolor(BLACK);
	}
	else if (player == -1)
	{
		setcolor(BLACK);
		setfillcolor(WHITE);
	}
	fillcircle(25 * y, 25 * x, 8);
}


int judge(int a, int b, int board_[16][16])
{
	for (int i = a - 1; i <= a + 1; i++)
		for (int j = b - 1; j <= b + 1; j++)
			if ((i > 0 && j > 0 && i < 16 && j < 16) && board_[i][j])
				return 1;
	return 0;
}


int MaxMin(int deep, int board_[16][16])
{
	int m_, a;
	int boardif[16][16];


	if (deep == 0)
	{
		return score(board_);
	}
	else if (deep % 2 == 0)
	{
		m_ = MIN;
		for (int i = 1; i <= 15; i++)
			for (int j = 1; j <= 15; j++)
			{
				if (board_[i][j] == 0 && judge(i, j, board_))
				{
					memcpy(boardif, board_, sizeof(int) * 256);
					boardif[i][j] = 2;
					if (end(i, j, boardif))
					{
						x = i;
						y = j;
						return MAX;
					}
					a = MaxMin(deep - 1, boardif);
					if (a > m_)
					{
						x = i;
						y = j;
						m_ = a;
					}
				}
			}
		return m_;
	}
	else
	{
		m_ = MAX;
		for (int i = 1; i <= 15; i++)
			for (int j = 1; j <= 15; j++)
			{
				if (board_[i][j] == 0 && judge(i, j, board_))
				{
					memcpy(boardif, board_, sizeof(int) * 256);
					boardif[i][j] = 1;
					if (end(i, j, boardif))
					{
						x = i;
						y = j;
						return MIN;
					}
					a = MaxMin(deep - 1, boardif);
					if (a < m_)
					{
						m_ = a;
						x = i;
						y = j;
					}
				}
			}
		return m_;
	}
}


int score(int board_[16][16])
{
	return score_1(2, board_) - score_1(1, board_) + score_2(2, board_) - score_2(1, board_);
}

int score_1(int a, int board_[16][16])
{
	int sum = 0;
	for (int i = 1; i <= 15; i++)
		for (int j = 1; j <= 15; j++)
			if (board_[i][j] == a)
			{
				for (int k = 0; k <= 3; k++)
				{
					int m;
					for (m = 1; i + m * derication[k][0] >= 1 && i + m * derication[k][0] <= 15 && j + m * derication[k][1] <= 15; m++)
					{
						if (board_[i + m * derication[k][0]][j + m * derication[k][1]] != a) break;
					}
					if (i - derication[k][0] >= 1 && i - derication[k][0] <= 15 && j - derication[k][1] >= 1 && j - derication[k][1] <= 15)
					{
						if (board_[i - derication[k][0]][j - derication[k][1]] == 0)
						{
							if (i + m * derication[k][0] >= 1 && i + m * derication[k][0] <= 15 && j + m * derication[k][1] >= 1 && j + m * derication[k][1] <= 15 && board_[i + m * derication[k][0]][j + m * derication[k][1]] == 0)
								sum += fenshu[m];																
							else
								sum += fenshu[m] / 10;															
						}
						else if (board_[i - derication[k][0]][j - derication[k][1]] != a)
							if (i + m * derication[k][0] >= 1 && i + m * derication[k][0] <= 15 && j + m * derication[k][1] >= 1 && j + m * derication[k][1] <= 15 && board_[i + m * derication[k][0]][j + m * derication[k][1]] == 0)
								sum += fenshu[m] / 10;															
					}
					else if (i + m * derication[k][0] >= 1 && i + m * derication[k][0] <= 15 && j + m * derication[k][1] >= 1 && j + m * derication[k][1] <= 15 && board_[i + m * derication[k][0]][j + m * derication[k][1]] == 0)
						sum += fenshu[m] / 10;
				}
			}
	return sum;
}

int score_2(int a, int board_[16][16])
{
	int sum = 0;
	for (int i = 1; i <= 15; i++)
		for (int j = 1; j <= 15; j++)
			if (board_[i][j] == a)
			{
				bool pan = 1;
				for (int m = -1;m <= 1;m++)
					for (int n = -1;n <= 1;n++)
					{
						if (i + m < 1 || i + m>15 || j + n < 1 || j + n>15)
							continue;
						if (board_[i + m][j + n] != 0 && (m != 0 || n != 0))
						{
							pan = 0;
							m = 2;
							break;
						}
					}

				if (pan)	sum++;
			}
	return sum;
}


int end(int a, int b, int board_[16][16])
{
	int o = board_[a][b];
	for (int i = 0;i <= 3;i++) {
		int k = 0;
		for (int j = -4;j <= 4;j++)
		{
			if (board_[a + j * derication[i][0]][b + j * derication[i][1]] == o && \
				a + j * derication[i][0] >= 1 && a + j * derication[i][0] <= 15 && \
				b + j * derication[i][1] >= 1 && b + j * derication[i][1] <= 15)
				k++;
			else k = 0;
			if (k == 5) return 1;
		}
	}
	return 0;
}
