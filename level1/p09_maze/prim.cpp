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

    creatMap();

    writeMap();
    printMap();
    return 0;
}


bool inside(int x,int y){
    return (x >= 1 && x < row-1 && y >= 1 && y < column -1);
}

void writeMap(){
    FILE* file = fopen(filePath,"w");
    fprintf(file,"size:%d*%d\n",column,row);
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; j++) {
            if (map[i][j]==1){
                fprintf(file,"%d",0);
            }else if (map[i][j]==0){
                fprintf(file,"%d",1);
            }else{
                fprintf(file,"%d",map[i][j]);
            }            
        }fprintf(file,"\n");
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
    srand((unsigned)time(nullptr));
    memset(map,0,sizeof(map));
    memset(visited,0,sizeof(visited));
    X.push_back(1);
    Y.push_back(1);
    int x0,y0;
    map[1][2]=1;
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
        if(count == 1) {
            x0 = x;y0 = y;
            map[x][y] = 1;
            for (int i = -1; i <= 1; i++){
                for (int j = -1; j <= 1;j++){
                    if (inside(x + i, y + j) && abs(i) + abs(j) == 1){//为了防止闭环，不能只选取一部分打通
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
            if(map[row-2][column-2]) map[row-2][column-2]=3;
            else map[x0][y0] = 3; //终点
        }
    }
    map[1][1] = 2;
    return;
}