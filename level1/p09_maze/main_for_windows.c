#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "maze.h"

int main(void) {
    unsigned int ch;
    Game game;

    while (1) {
        printf("Please enter the filename: ");
        scanf("%s", game.filename);
        getchar();
        init_game(&game);
        if (game.maze == NULL) {
            printf("%s not found!\n", game.filename);
        } else {
            break;
        }
    }

    system("CLS");
    print_maze(&game);
    printf("Use arrow keys or wasd to move or enter q to quit.\n");

    while ((ch = getch()) != 'q') {
        if (ch == 0 || ch == 224) {
            // Use arrow keys
            switch (getch()) {
                case 72: // Up
                    move(&game, 0);
                    break;

                case 80: // Down
                    move(&game, 1);
                    break;

                case 77: // Right
                    move(&game, 2);
                    break;

                case 75: // Lift
                    move(&game, 3);
                    break;

                default:
                    break;
            }
        } else {
            // Use w a s d
            switch (ch) {
                case 'w':
                case 'W': // Up
                    move(&game, 0);
                    break;

                case 's':
                case 'S': // Down
                    move(&game, 1);
                    break;

                case 'd':
                case 'D': // Right
                    move(&game, 2);
                    break;

                case 'a':
                case 'A': // Lift
                    move(&game, 3);
                    break;

                default:
                    break;
            }
        }

        system("CLS");
        print_maze(&game);

        if (game.x == game.target_x && game.y == game.target_y) {
            printf("Success!\n");
            getchar();
            break;
        } else {
            printf("Use arrow keys or wasd to move or enter q to quit.\n");
        }
    }

    quit_game(&game);

    return 0;
}
