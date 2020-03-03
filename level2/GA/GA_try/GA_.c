//
// Created by asus on 2020/3/2.
//

#include "GA_.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


static void newPeoples(const people* peoples, people* baby1 , people* baby2, double allProbable);

void InitPeoples(people* peoples)
{
    for(int i = 0; i < POPULATION_SIZE; i++) {
        for(int j = 0; j < DNA_LENGTH; j++) {
            peoples[i].dna[j] = rand() % KINDS_MOVE + '0';
        }
        peoples[i].fitness_value = 0;
    }
}
void move_person(const people* people1, int* x, int* y, const int maze[][ROW])
{
    for(int i = 0;i < DNA_LENGTH; ++i) {
        switch (people1->dna[i]) {
            case UP:
                if (maze[*x - 1][*y] != WALL_NUM) {
                    *x -= 1;
                }
                break;
            case DOWN:
                if (maze[*x + 1][*y] != WALL_NUM) {
                    *x += 1;
                }
                break;
            case LEFT:
                if (maze[*x][*y - 1] != WALL_NUM) {
                    *y -= 1;
                }
                break;
            case RIGHT:
                if (maze[*x][*y + 1] != WALL_NUM) {
                    *y += 1;
                }
                break;
            default:break;
        }
    }
}
void EvaluatePerson(people* people1, int x, int y)
{
    double destination = (X_D - x) * (X_D - x) + (Y_D - y) * (Y_D - y);
    destination = sqrt(destination);
    people1->fitness_value = 100.0 - 100.0/MAX_DESTINATION*destination;
}
people* Crossing(people* peoples)
{
    double allProbable = 0;
    for(int i = 0; i < POPULATION_SIZE; i++) {
        allProbable += peoples[i].fitness_value;
    }
    people* new_peoples = (people*)malloc(sizeof(people) * POPULATION_SIZE);
    if(new_peoples == NULL) {
        exit(-9);
    }
    else {
        for(int i = 0;i < POPULATION_SIZE; i += 2) {
            newPeoples(peoples,&new_peoples[i],&new_peoples[i+1],allProbable);
        }
        free(peoples);
        return new_peoples;
    }
}
static void newPeoples(const people* peoples, people* baby1 , people* baby2, double allProbable)
{

    double r1 = rand() % ((int)allProbable+1);
    double r2 = rand() % ((int)allProbable+1);
    int i = 0, j = 0;
    for(i = 0; r1 > 0 && i< POPULATION_SIZE;++i) {
        r1 -= peoples[i].fitness_value;
    }
    for(j = 0;r2 > 0 && j< POPULATION_SIZE;++j) {
        r2 -= peoples[j].fitness_value;
    }
    j -= 1;
    i -= 1;
    double c_rant = 1.0 * rand() / RAND_MAX;
    if(c_rant < CROSSING_RATE) {
        int wz = rand() % DNA_LENGTH;
        baby1->fitness_value = 0.0;
        baby2->fitness_value = 0.0;
        for(int k = 0 ; k < wz; ++k) {
            baby1->dna[k] = peoples[i].dna[k];
            baby2->dna[k] = peoples[j].dna[k];
        }
        for(int k = wz; k < DNA_LENGTH; ++k) {
            baby1->dna[k] = peoples[j].dna[k];
            baby2->dna[k] = peoples[i].dna[k];
        }
    }
    else {
        for(int k = 0; k < DNA_LENGTH; ++k) {
            baby1->dna[k] = peoples[i].dna[k];
        }
        for(int k = 0; k < DNA_LENGTH; ++k) {
            baby2->dna[k] = peoples[j].dna[k];
        }
        baby1->fitness_value = 0;
        baby2->fitness_value = 0;
    }
}
void variation(people* peoples)
{
    int wz = 0;
    for(int i = 0;i < POPULATION_SIZE; ++i) {
        if( 1.0 * rand() / RAND_MAX < VARIATION_RATE) {
            wz = rand() % DNA_LENGTH;
            peoples[i].dna[wz] = rand() % KINDS_MOVE + '0';
        }
    }
}

void print_peoples(const people* peoples)
{
    for(int i = 0; i < POPULATION_SIZE; ++i) {
        printf("%d : ", i+1);
        for(int j = 0; j < DNA_LENGTH ; ++j) {
            printf("%c",peoples[i].dna[j]);
        }
        printf("   %lf\n",peoples[i].fitness_value);
    }
}