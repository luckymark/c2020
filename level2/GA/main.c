#include <stdio.h>
#include "GA.h"

int main() {
    GA ga;
    int success_genome = -1;

    create_start_population(&ga);
    print_maze(&(ga.genomes_array[0].game));
    printf("The generation is %d\n", ga.generation);

    for (int i = 0; i < MAX_GENERATIONS; ++i) {
        if (ga.best_fitness_score == 1.0) {
            printf("\nFound it!\n");
            for (int j = 0; j < GENOMES_NUM; j++) {
                if (ga.genomes_array[j].fitness == 1.0) {
                    success_genome = j;
                    break;
                }
            }
            break;
        }
        epoch(&ga);
        printf("The generation is %d\n", ga.generation);
    }

    if (success_genome == -1) {
        printf("\nNot found!\n");
    } else {
        int *moves_array = decode(ga.genomes_array[success_genome].bits_array);
        for (int i = 0; i < BITS_NUM / 2; i++) {
            init_game(&(ga.genomes_array[success_genome].game));
            switch (moves_array[i]) {
                case 0:
                    printf("Up ");
                    break;
                case 1:
                    printf("Down ");
                    break;
                case 2:
                    printf("Right ");
                    break;
                case 3:
                    printf("Left ");
                    break;
                default:
                    break;
            }
            if (move(&(ga.genomes_array[success_genome].game), moves_array[i])) {
                break;
            }
        }
    }

    return 0;
}
