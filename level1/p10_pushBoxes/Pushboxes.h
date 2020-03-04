#define sp "                    "

int steps[5];       // 每张map的最少步数。
char option;		// 菜单中用户的选择。
int a;				// 人物x方向上的位置。
int b;				// 人物y方向上的位置。
char maze[20][35];	// 保存文件数据的数组。
int flag;			// 判断现在进行的是哪个map。
int rood;           // 每句游戏走的步数。