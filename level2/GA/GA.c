#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GA.h"

double rand_f() {
    return rand()/(RAND_MAX+1.0);
}

void mutate(Genome *genome) {
    for (int i = 0; i < BITS_NUM; i++) {
        if (rand_f() < MUTATION_RATE) {
            genome->bits_array[i] = 1 - genome->bits_array[i];
        }
    }
}

void crossover(Genome *parent1, Genome *parent2, Genome *baby1, Genome *baby2) {
    if (rand_f() > CROSSOVER_RATE || parent1 == parent2) {
        memcpy(baby1->bits_array, parent1->bits_array, sizeof(int) * BITS_NUM);
        memcpy(baby2->bits_array, parent2->bits_array, sizeof(int) * BITS_NUM);
        return;
    }
    int cp = floor(rand_f() * BITS_NUM);
    for (int i = 0; i < cp; i++) {
        baby1->bits_array[i] = parent1->bits_array[i];
        baby2->bits_array[i] = parent2->bits_array[i];
    }
    for (int i = cp; i < BITS_NUM; i++) {
        baby1->bits_array[i] = parent2->bits_array[i];
        baby2->bits_array[i] = parent1->bits_array[i];
    }
}

int roulette_wheel_selection(GA *ga) {
    double slice = rand_f() * ga->total_fitness_score;
    double total = 0;
    int selected_genome;
    for (selected_genome = 0; selected_genome < GENOMES_NUM; selected_genome++) {
        total += ga->genomes_array[selected_genome].fitness;
        if (total > slice) {
            break;
        }
    }
    return selected_genome;
}


void update_fitness_scores(GA *ga) {
    ga->total_fitness_score = 0;
    ga->best_fitness_score = 0;
    for (int i = 0; i < GENOMES_NUM; i++) {
        int *moves_array = decode(ga->genomes_array[i].bits_array);
        for (int j = 0; j < BITS_NUM/2; j++) {
            move(&(ga->genomes_array[i].game), moves_array[j]);
        }
        unsigned int diff_x = abs((int)ga->genomes_array[i].game.x - (int)ga->genomes_array[i].game.target_x);
        unsigned int diff_y = abs((int)ga->genomes_array[i].game.y - (int)ga->genomes_array[i].game.target_y);
        ga->genomes_array[i].fitness = 1.0 / (diff_x + diff_y + 1);
        ga->total_fitness_score += ga->genomes_array[i].fitness;
        if (ga->genomes_array[i].fitness > ga->best_fitness_score) {
            ga->best_fitness_score = ga->genomes_array[i].fitness;
        }
        free(moves_array);
    }
}

int *decode(const int *bits_array) {
    int bit[2];
    int *moves_array = (int*)malloc(sizeof(int) * (BITS_NUM / 2));
    for (int i = 0; i < BITS_NUM / 2; i += 2) {
        bit[0] = bits_array[i];
        bit[1] = bits_array[i+1];
        moves_array[i] = bit_to_int(bit);
    }
    return moves_array;
}

int bit_to_int(const int *bit) {
    int move = 0;
    switch (bit[0]) {
        case 0:
            switch (bit[1]) {
                case 0:
                    move = 0; // Up
                    break;
                case 1:
                    move = 1; // Down
                    break;
                default:
                    break;
            }
            break;
        case 1:
            switch (bit[1]) {
                case 0:
                    move = 2; // Right
                    break;
                case 1:
                    move = 3; // Left
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return move;
}

void create_start_population(GA *ga) {
    srand(time(NULL));
    for (int i = 0; i < GENOMES_NUM; i++) {
        init_game(&(ga->genomes_array[i].game));
        for (int j = 0; j < BITS_NUM; j++) {
            ga->genomes_array[i].bits_array[j] = rand() % 2;
        }
    }
    ga->generation = 0;
    update_fitness_scores(ga);
}

void epoch(GA *ga) {
    int babies = 0;
    Genome babies_array[GENOMES_NUM];
    while (babies < GENOMES_NUM) {
        int parent1 = roulette_wheel_selection(ga);
        int parent2 = roulette_wheel_selection(ga);
        crossover(&(ga->genomes_array[parent1]), &(ga->genomes_array[parent2]), &babies_array[babies], &babies_array[babies+1]);
        mutate(&babies_array[babies]);
        mutate(&babies_array[babies+1]);
        babies += 2;
    }
    for (int i = 0; i < GENOMES_NUM; i++) {
        memcpy(ga->genomes_array[i].bits_array, babies_array[i].bits_array, BITS_NUM * sizeof(int));
        init_game(&(ga->genomes_array[i].game));
    }
    (ga->generation)++;
    update_fitness_scores(ga);
}
