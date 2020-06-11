#include<time.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#define min(x,y) (x>y?y:x)
#define max(x,y) (x>y?x:y)
const int LEN=15;
const int LAYER=4;
const int MAXN=LEN+2;
const int INF=3e8;
const int MAXDIFF=3;
const int MAXSAME=8;
const int MAXSPACE=4;
const int MATCHES=15;
const int MAXTOP=LEN*LEN/4;
char title[30]="title Gobang  OmegaGO ver2.1";
int value[MAXN][MAXN],init[MAXN][MAXN],stx[MAXN*MAXN],sty[MAXN*MAXN],sco[MAXSAME][MAXDIFF][MAXSPACE];
int top=0,mx[MAXN],rx[MAXN],ry[MAXN],randsco[MAXSAME][MAXDIFF][MAXSPACE],cntwin,cntlose,totwin,totlose,mxcal0,mxcal1;
int vis[LAYER][MAXN][MAXN]; 
char ch[11][4]={"©°","©Ð","©´","©À","©à","©È","©¸","©Ø","©¼","¡ñ","¡ð"};
void startgame(); 
inline bool check(int x,int y);
void mainmenu();
void train();
void single();
void robot(int type);
void retract();
void goto_xy(int x,int y);
int win();
void printboard(int y,int x,int player);
int cal(int type);
void defeat();
void victory();
void introduce();
void empty();
void fread();
void initialize();
inline int val(int same,int diff,int space,int type);
int dfs(int step,int player,int alpha,int beta,int type,int lastx,int lasty);

