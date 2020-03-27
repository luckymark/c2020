#ifndef GA_GA_H
#define GA_GA_H

#include "maze.h"

#define BITS_NUM 30 // 每个基因组上的 bits 数

double rand_f();

typedef struct {
    int bits_array[BITS_NUM]; // 基因序列
    double fitness; // 适应性分数
    Game game;
} Genome;

#define GENOMES_NUM 20
#define CROSSOVER_RATE 0.7
#define MUTATION_RATE  0.001
#define MAX_GENERATIONS 10000000

typedef struct {
    Genome genomes_array[GENOMES_NUM]; // 基因组群体
    int fittest_genome;
    double best_fitness_score;
    double total_fitness_score;
    int generation; // 代数
} GA;

void mutate(Genome *genome);
void crossover(Genome *parent1, Genome *parent2, Genome *baby1, Genome *baby2);
int roulette_wheel_selection(GA *ga);
void update_fitness_scores(GA *ga);
int *decode(const int *bits_array);
int bit_to_int(const int *bit);
void create_start_population(GA *ga);
void epoch(GA *ga);

#endif //GA_GA_H
