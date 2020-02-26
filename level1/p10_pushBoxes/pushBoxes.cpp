#include<stdio.h>
#include<conio.h>
#include<windows.h>
int Len, Height;/*地图的长宽*/
const int cor_x = 6;/*输出在console的原点*/
const int cor_y = 6;
const int pos_tip_x = 1;/*提示语输出的起点*/
const int pos_tip_y = 6;
const int score_pos_x = 3;/*分数输出的起点*/
const int score_pos_y = 6;
HANDLE hOut;
DWORD a;
int mp[50][50],num;/*mp数组表示整张地图 0空地 1 目标点 2 箱子 3 墙 4人 5 人在目标点上 6 箱子在目标点上*/
int cnt_goal = 0;
COORD point;
int score = 0;
/*注由于符号一个占两个长度故在转化成console的坐标时记得乘2*/
struct node{
	int x,y;
};

void pf_score()/*打印分数*/
{
	COORD pos_score = {score_pos_y, score_pos_x};
	CONSOLE_CURSOR_INFO CursorInfo;
	
	GetConsoleCursorInfo(hOut, &CursorInfo);
	CursorInfo.bVisible = false;
	SetConsoleCursorInfo(hOut, &CursorInfo);
	SetConsoleCursorPosition(hOut, pos_score);
	FillConsoleOutputCharacter(hOut, ' ', 15, pos_score, &a);
	printf("score:%d",score);
	return;
}


char* itoc(int x)
{
	char s[10];
	int num[10], cnt = 0, i;
	while(x) num[cnt++] = x % 10,/*Êý×Ö×ª×Ö·û´®*/
	x /= 10;
	
	for(i = 0;i < cnt ;i++)
	s[i] = num[cnt - i - 1] + '0';
	s[cnt] = '\0';
	return strdup(s);
}


//void pf()
//{
//	int i,j;
//	for(i = 1;i <= Height;i++)
//	{
//		for(j = 1;j <= Len;j++)
//		printf("%d ",mp[i][j]);
//		printf("\n");
//	}
//}
void load_mp()/*¼ÓÔØµØÍ¼*/ 
{
	FILE *fin;
	char *s1, *s2,*s3;
	char str[30] = "";
	int str_x,str_y;
	
	
	s1 = "map";
	s2 = itoc(num);
	s3 = ".txt"; 
	strcpy(str, s1);
	strcat(str, s2);
	strcat(str, s3);
	
	
	fin = fopen(str, "r");
	int i, j, x, y;
	
	fscanf(fin,"%d%d",&Height, &Len);
	/*0 space 1 goal_place 2 box 3 wall 4 peo 5 peo on the goal 6 box on the goal*/
	for(i = 1;i <= Height;i++)
	for(j = 1;j <= Len;j++)
	{
		fscanf(fin,"%d",&mp[i][j]);
		COORD pr_pos = {j * 2 - 2 + cor_y, i * 2 - 2 + cor_x};
		if(mp[i][j] == 1)
		{
			cnt_goal++;
			WriteConsoleOutputCharacter(hOut, "¡õ", 2, pr_pos, &a);
		}
		else if(mp[i][j] == 2) WriteConsoleOutputCharacter(hOut, "¡ö", 2, pr_pos, &a);
		else if(mp[i][j] == 3) WriteConsoleOutputCharacter(hOut, "¡ñ", 2, pr_pos, &a);
		else if(mp[i][j] == 4) WriteConsoleOutputCharacter(hOut, "¡â", 2, point = pr_pos, &a);
		else if(mp[i][j] == 0) WriteConsoleOutputCharacter(hOut, "¡ð", 2, pr_pos, &a);
	}
	fclose(fin);
	
} 
void load_tip()/*加载提示语*/
{
	COORD CursorPosition = {pos_tip_y, pos_tip_x};
	SetConsoleCursorPosition(hOut, CursorPosition);
	printf("·½Ïò¼ü¿ØÖÆ·½Ïò0ÍË³ö\n");
	CursorPosition.Y++;
	SetConsoleCursorPosition(hOut, CursorPosition);
	printf("·ÖÊý½«±£´æÔÚ¶ÔÓ¦µØÍ¼±àºÅ_score.txtÖÐ\n");
}

void creat_mp()/*创建地图*/
{
	printf("ÇëÊäÈëÄãÒªÑ¡ÔñµÄµØÍ¼±àºÅ");
	scanf("%d",&num);
	system("cls");
	load_mp();
}



int dir[4][2]={{-1, 0}, {1, 0}, {0, -1}, {0, 1}};/*控制方向*/
void move_block(int d, char* blo, int sgn, node &pos)/*移动方块和人*/
{
	if(mp[pos.x + dir[d][0]][pos.y + dir[d][1]] != 0 && mp[pos.x + dir[d][0]][pos.y + dir[d][1]] != 1) return;/*是否越界或遇到障碍*/
	COORD block = {cor_y + pos.y * 2 - 2, cor_x + pos.x * 2 - 2};
	if(mp[pos.x][pos.y] == 5 || mp[pos.x][pos.y] == 6)/*方块是否移出目标区域*/
	{
		WriteConsoleOutputCharacter(hOut, "¡õ", 2, block, &a);
		if(mp[pos.x][pos.y] == 6) score--;
		mp[pos.x][pos.y] = 1;
	}
	else
	{
		WriteConsoleOutputCharacter(hOut, "¡ð", 2, block, &a);
		mp[pos.x][pos.y] = 0;
	}
	pos.x = pos.x + dir[d][0];
	pos.y = pos.y + dir[d][1];
	block = {cor_y + pos.y * 2 - 2, cor_x + pos.x * 2 - 2};
	if(sgn == 2 && mp[pos.x][pos.y] == 1)
	{
		score++;
		sgn = 6;
	}
	else if(sgn == 4 && mp[pos.x][pos.y] == 1) sgn = 5;
	WriteConsoleOutputCharacter(hOut, blo, 2, block, &a);
	mp[pos.x][pos.y] = sgn;
	
}


void Save()/*保存分数*/
{
	char *s1, *s2;
	FILE *fOut;
	s1 = itoc(num);
	s2 = "_score.txt";
	strcat(s1, s2);
	fOut = fopen(s1, "w");
	fprintf(fOut, "ÄúµÄµÃ·ÖÊÇ£º%d",score);
	COORD pos_pf = {cor_y + Len * 2, cor_x + Height * 2 + 4};
	SetConsoleCursorPosition(hOut, pos_pf);
	fclose(fOut);
}
void work()
{//0 exit 
	node player;
	player.x = ((point.Y - cor_x) + 2) / 2;
	player.y = ((point.X - cor_y) + 2) / 2;
	pf_score();
	while(1)
	{
		char c = getch();//up 72 down 80 left 75  rignt 77
		if(c == '0') 
		{
			Save();
			exit(0);
		}
		c = getch();
		node block = player;
		int d;
		if(c == 72)
		{
			block.x--;
			d = 0;
		}
		
		else if(c == 80)
		{
			block.x++;
			d = 1;
		}
		
		else if(c == 75)
		{
			block.y--;
			d = 2;
		}
		
		else if(c == 77)
		{
			block.y++;
			d = 3;
		}
		if(mp[block.x][block.y] == 2 || mp[block.x][block.y] == 6)
		move_block(d, "¡ö", 2, block);
		move_block(d, "¡â", 4, player);
		pf_score();
		if(score == cnt_goal)
		{
			COORD pos_pf = {cor_y + Len * 2, cor_x + Height * 2 + 2};
			SetConsoleCursorPosition(hOut, pos_pf);
			printf("You Win!");
			Save();
			break;
		}
	}
}


int main(void)
{
	memset(mp,-1,sizeof(mp));
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	creat_mp();
	load_tip();
	work();
	CloseHandle(hOut);
}
