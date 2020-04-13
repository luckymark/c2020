//
// Created by 20694 on 2020/4/12.
//

#include "aboutmap.h"
int m,n;
int main(int argc, char *argv[]) {
    pos loc;
    FILE*in,*out;
    int i, j, x, y, a, b;
    i=j=x=y=a=b=0;
    int cnt=0;
    int level=0;
    char step;
    int judge=1;
    elemtype map[row][col]={0};
    char Filenames[5][25]={
            "C:\\untitled\\level1.txt",
            "C:\\untitled\\level2.txt",
            "C:\\untitled\\level3.txt",
            "C:\\untitled\\level4.txt",
            "C:\\untitled\\level5.txt"
    };
//    elemtype map[row][col]={2,3,2,2,2,
//    2,1,1,2,2,
//    2,2,1,2,2,
//    2,2,1,2,2,
//    2,2,3,2,2};C:\untitled\cmake-build-debug\untitled.exe
while(level<5) {
    in = fopen(Filenames[level], "r");
    f(i, 5, 0)f(j, 5, 0) {
            fscanf(in, "%d", &map[i][j]);
        }
    loc.cnt=loc.bag=0;
    puts("Please use 'w','a','s','d' to move");
    f(i, 5, 0)f(j, 5, 0) {
            switch (map[i][j]) {
                case 1: {
                    if (4 == j) printf(" \n"); else printf(" ");
                    break;
                }
                case 2: {
                    if (4 == j) printf("*\n"); else printf("*");
                    break;
                }
                case 3: {
                    if (4 == j) printf("#\n"); else printf("#");
                    loc.x = i;
                    loc.y = j;
                    break;
                }
                case 4: {
                    if (4 == j) printf("=\n"); else printf("=");
                    break;
                }
                case 5: {
                    if (4 == j) printf("[\n"); else printf("[");
                    break;
                }
                case 6: {
                    if (4 == j) printf("@\n"); else printf("@");
                    a = i;
                    b = j;
                    break;
                }
                default:{
                    puts("errors in the files");
                    return 0;
                }
            }
        }
    while (1) {
        scanf("%c", &step);
        if ('W' == step || 'w' == step) { loc = Switch(map, 'W', loc); }
        else if ('A' == step || 'a' == step) { loc = Switch(map, 'A', loc); }
        else if ('S' == step || 's' == step) { loc = Switch(map, 'S', loc); }
        else if ('D' == step || 'd' == step) { loc = Switch(map, 'D', loc); }
        f(i, 5, 0)f(j, 5, 0){
            if(5==map[i][j]){
                judge=0;
            }else judge=1;
        }
        if (loc.x == a && loc.y == b&& judge==1) {
            system("cls");
            getch();
            break;
        }
        system("cls");
        f(i, 5, 0)f(j, 5, 0) {
                switch (map[i][j]) {
                    case 1: {
                        if (4 == j) printf(" \n"); else printf(" ");
                        break;
                    }
                    case 2: {
                        if (4 == j) printf("*\n"); else printf("*");
                        break;
                    }
                    case 3: {
                        if (4 == j) printf("#\n"); else printf("#");
                        break;
                    }
                    case 4: {
                        if (4 == j) printf("=\n"); else printf("=");
                        break;
                    }
                    case 5: {
                        if (4 == j) printf("[\n"); else printf("[");
                        break;
                    }
                    case 6: {
                        if (4 == j) printf("@\n"); else printf("@");
                        break;
                    }
                    default:{
                        puts("errors in the files");
                        return 0;
                    }
                }
            }
    }
    out = fopen(Filenames[level], "w");
    if(4==level){
    fprintf(out,"you have finished level%d,your score is %d\nyou have won",level+1,20-loc.cnt);
    }else {
        fprintf(out,"you have finished level%d,your score is %d",level+1,60-loc.cnt);
    }
    level++;
}
}