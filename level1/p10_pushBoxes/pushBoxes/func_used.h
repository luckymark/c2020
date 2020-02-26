#ifndef FUNC_USED
#define FUNC_USED

typedef struct __PER_BOX__ {
	int hang;
	int lie;
}Upthing;

#define LINE 5 // 迷宫行数
#define ROW  5 // 迷宫列数
#define BOX_DES  2 // 箱子目的地的值
#define WALL_NUM 1 // 墙的值
#define SPACE_NUM 0 // 空地方的值
#define UP 'w'    // 向上
#define DOWN 's'  // 向下
#define LEFT 'a'  // 向左
#define RIGHT 'd' // 向右
#define ONE_SECOND 1000  //Sleep函数中一秒的值

/* 开启新的游戏 */
void new_game();

/* 返回游戏是否结束 */
/* 游戏结束返回true */
bool isGameover(Upthing*, int, int[][ROW]);

/* 清空先前的形势并打印当前形势*/
void print_game(const int[][ROW], Upthing*, int);

/* 返回是否成功移动 */
bool move_person_box(Upthing*, int, int[][ROW]);

/* 返回是否可以移动 */
/* 通过更改ID_box来获取需要移动的箱子的号码 */
bool move_or_not(char, Upthing*, int, const int[][ROW], int*);

/* 返回当前位置是几号箱子 */
/* 0表示没有箱子 */
int isBOX(Upthing*, int, int, int);

#endif 

