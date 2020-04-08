#include "aboutmap.h"
int m,n;
int main() {
    int i, j;
    int x = 0;
    int y = 2;
    int win = 0;
    char step;
    char map[row][col] = {{'#', '#', 'a', '#', '#'},
                          {'#', ' ', ' ', '#', '#'},
                          {'#', ' ', '#', '#', '#'},
                          {'#', ' ', ' ', '#', '#'},
                          {'#', '#', 'b', '#', '#'}};

    puts("Please use 'w','a','s','d' to move");
    f(i, 5, 0)
        f(j, 5, 0) {
            if (4 == j) printf("%c\n", map[i][j]);
            else printf("%c", map[i][j]);
        }
    while (0 == win) {
        scanf("%c", &step);
        if('W'==step||'w'==step) {x=Switch(map,'W',x,y);}
        else if ('A'==step||'a'==step) {y=Switch(map,'A',x,y);}
        else if ('S'==step||'s'==step) {x=Switch(map,'S',x,y);}
        else if ('D'==step||'d'==step) {y=Switch(map,'D',x,y);}
        if(x==4&&y==2){
            system("cls");
            printf("you win\n");
            getch();
            return 0;
        }
        f(n, 5, 0)
            f(m, 5, 0)
            {
                if(map[n][m]=='a'+'b'-' '){
                    win=1;
                }
            }
        system("cls");
        f(i, 5, 0)
            f(j, 5, 0) {
                if (4 == j) printf("%c\n", map[i][j]);
                else printf("%c", map[i][j]);
            }
    }
//    scanf("%c",&step);
//    Switch((char**)map,step,x,y);
    f(i, 5, 0)
        f(j, 5, 0) {
            if (4 == j) printf("%c\n", map[i][j]);
            else printf("%c", map[i][j]);
        }
}