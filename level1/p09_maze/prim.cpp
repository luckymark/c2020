#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <algorithm>

#define MAXN 50
using namespace std;
int row,column; //行和列
int map[MAXN][MAXN];
bool visited[MAXN][MAXN];
char filePath[50] = "C://Users//ZYW//temp//map.txt";

vector<int> X;
vector<int> Y;

bool inside(int x,int y);
void writeMap();
void printMap();
void creatMap();


int main() {
    printf("please input the number of column and row:");
    scanf("%d%d",&column,&row);
    srand((unsigned)time(nullptr));
    memset(map,0,sizeof(map));
    memset(visited,0,sizeof(visited));

    map[1][0] = 1;
    X.push_back(1);
    Y.push_back(1);
    creatMap();
    map[1][0] = 0;
    map[1][1] = 2;

    writeMap();
    printMap();
    return 0;
}


bool inside(int x,int y){
    return (x >= 1 && x < row-1 && y >= 1 && y < column -1);
}


void writeMap(){
    FILE* file = fopen("C://Users//ZYW//temp//map.txt","w");
    fprintf(file," %d*%d\n",column,row);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; j++) {
            fprintf(file,"%d",map[i][j]);
        }
        fprintf(file,"\n");
    }fclose(file);
}
void printMap(){
    printf("size:%d*%d\n",column,row);
    for (int i=0;i<row;i++) {
        for (int j=0;j<column;j++) {
            printf("%d",map[i][j]);
        }
        printf("\n");
    }
}           

void creatMap(){
    int x0,y0;
    while(X.size()){
        int r = rand() % X.size();
        int x = X[r];
        int y = Y[r];
        int count = 0;  //上下左右的空格
        for (int i=-1;i<=1;i++){
            for (int j=-1;j<=1;j++){
                if(abs(i)+abs(j) == 1){
                    if(map[x+i][y+j] == 1){
                        count++;
                    }
                }
            }
        }
        if(count == 1) {//如果只有一条路，就把周围都设成通路
            x0 = x;y0 = y;
            map[x][y] = 1;
            for (int i = -1; i <= 1; i++){
                for (int j = -1; j <= 1;j++){
                    if (inside(x + i, y + j) && abs(i) + abs(j) == 1){
                        if(!map[x+i][y+j] && !visited[x+i][y+j]){
                            X.push_back(x+i);
                            Y.push_back(y+j);
                            visited[x+i][y+j] = 1;
                        }
                    }
                }                    
            }
        }
        X.erase(X.begin() + r);
        Y.erase(Y.begin() + r);
        if(!X.size()){
            map[x0][y0] = 3; //终点
        }
    }return;
}