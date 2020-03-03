//
// Created by asus on 2020/3/2.
//

#ifndef GA_TRY_GA__H
#define GA_TRY_GA__H

//
#define POPULATION_SIZE 200
#define DNA_LENGTH  80
#define CROSSING_RATE 0.7
#define VARIATION_RATE 0.001
#define COUNT 10000000

// maze def
#define UP '0'
#define DOWN '1'
#define LEFT '2'
#define RIGHT '3'
#define ROW 20
#define LINE 20
#define X_D 19
#define Y_D 15
#define MAX_DESTINATION 25
#define WALL_NUM 1
#define KINDS_MOVE 4


typedef struct _people_{
    char dna[DNA_LENGTH];
    double fitness_value;
} people;

void InitPeoples(people* peoples);
void move_person(const people* people1, int* x, int* y, const int maze[][ROW]);
void EvaluatePerson(people* people, int x, int y);
people* Crossing(people* peoples);
void variation(people* peoples);
void print_peoples(const people* peoples);

#endif //GA_TRY_GA__H
