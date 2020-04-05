//
// Created by 彭琳峰 on 2020/4/5.
//

#ifndef GA_MAZE_GA_H
#define GA_MAZE_GA_H
class GA
{
private:
    int m_popsize;
    int m_chromosome_length;
    double m_mutation_rate;
    double m_crossover_rate;
    typedef struct Individual{
        int number;
        int fitness;
        int chromosome[];
        double select_rate;
    }individual;
    GA(){
        m_popsize = 10;
        m_chromosome_length = 50;
        m_mutation_rate = 0.1;
        m_crossover_rate = 0.7;
    }

public:
    void Crossover(int chromo1[],int chromo2[]);
    void Mutation(int chromosome[])
};
#endif //GA_MAZE_GA_H
