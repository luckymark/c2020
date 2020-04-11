#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_X 25
#define MAX_Y 25
#define MAX_ROUND 3

const char dchar[7][3] = {"  ", "▓", "□", "■", "●", "■", "●"};
const char dirs[2][12] = {"maps", "history.csv"};
int X, Y, x, y, n_box, sharp, step;
int map[MAX_X][MAX_Y];

void refresh();
void loadMap();
void history();
int  pushBox(int x, int y, int dx, int dy);

int main() {
    system("title pushBoxes");
    for (sharp = 1; sharp <= MAX_ROUND; sharp++) {
        BEGINNER:
        step = 0;
        loadMap();
        refresh();
        while (1) {
            if (kbhit()) {
                int dx, dy, move = 1;
                switch (getch()) {
                    case 72: dx = -1, dy = 0; break; // ↑
                    case 80: dx = +1, dy = 0; break; // ↓
                    case 75: dy = -1, dx = 0; break; // ←
                    case 77: dy = +1, dx = 0; break; // →
                    case  8: goto BEGINNER; // ←Backspace
                    default: move = 0;
                }
                if (move) {
                    if (pushBox(x, y, dx, dy)) {
                        x += dx, y += dy, step++;
                        refresh();
                        if (n_box == 0)
                            break;
                    }
                }
            }
        }
        history();
    }
    printf("\nYou win!\n");
    system("pause");
    return 0;
}

int pushBox(int x, int y, int dx, int dy) {
    int tx = x + dx, ty = y + dy;
    if (tx < 0 || ty < 0 || tx >= X || ty >= Y)
        return 0;
    switch (map[tx][ty]) {
        case 0:
            n_box += map[x][y] == 5;
            map[tx][ty] = map[x][y] - (map[x][y] >  4) * 2;
            map[ x][ y] = map[x][y] > 4 ? 2 : 0;
            return 1;
        case 2:
            n_box -= map[x][y] == 3;
            map[tx][ty] = map[x][y] + (map[x][y] <= 4) * 2;
            map[ x][ y] = map[x][y] > 4 ? 2 : 0;
            return 1;
        case 3: case 5:
            if (pushBox(tx, ty, dx, dy))
                return pushBox(x, y, dx, dy);
        default: return 0;
    }
}

void refresh() {
    system("cls");
    printf("Round #%d Step %d", sharp, step);
    for (int i = 0; i < X; i++) {
        printf("\n ");
        for (int j = 0; j < Y; j++) {
            printf("%s", dchar[map[i][j]]);
        }
    }
}

void loadMap() {
    char temp[100];
    sprintf(temp, "%s/%d.txt", dirs[0], sharp);
    if (freopen(temp, "r", stdin) == NULL) {
        freopen("con", "r", stdin);
        puts("\nError: Map Lost!");
        system("pause");
        exit(0);
    }
    scanf("%d%d%d%d%d", &X, &Y, &x, &y, &n_box);
    sprintf(temp, "mode con lines=%d cols=%d", X + 2, Y * 2 + 2);
    system(temp);
    sprintf(temp, "pushBoxes #%d", sharp);
    system(temp);
    for (int i = 0; i < X; i++) {
        for (int j = 0; j < Y; j++) {
            scanf("%d", &map[i][j]);
        }
    }
    freopen("con", "r", stdin);
}

void history() {
    FILE *fp = fopen(dirs[1], "a");
    if (sharp == 1) {
        char _asctime[30];
        struct tm* tblock;
        time_t timer = time(NULL);
        tblock = localtime(&timer);
        sprintf(_asctime, "%s", asctime(tblock));
        _asctime[strlen(_asctime) - 1] = '\0';
        fprintf(fp, "\n%s", _asctime);
    }
    fprintf(fp, ",%d", step);
}
