#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;
//设置迷宫长宽，墙和路径的值，RANK调整挖墙深度
#define  L 13
#define WALL 0
#define ROUTE 1
#define PERSON -1
int maze[L][L]={
        0,0,0,0,0,0,0,0,0,0,0,0,0,
        1,1,1,1,1,1,0,0,0,0,1,0,0,
        0,0,0,0,0,1,0,0,0,0,1,0,0,
        0,1,0,0,0,1,0,0,0,0,1,0,0,
        0,1,0,0,0,1,1,1,1,1,1,1,0,
        0,1,0,0,0,1,0,0,0,0,1,0,0,
        0,1,1,0,0,1,0,0,0,0,0,1,0,
        0,1,0,1,1,1,1,1,1,1,1,1,0,
        0,1,0,0,0,1,1,0,0,0,0,1,0,
        0,1,0,1,1,1,1,1,1,1,0,1,0,
        0,1,0,0,0,0,1,0,0,0,0,1,0,
        0,0,1,1,1,1,1,1,1,1,1,1,1,
        0,0,0,0,0,0,0,0,0,0,0,0,0,

};
int flag[L][L]={0};
//设置GA参数
#define POP_SIZE 10
#define CHROMOSOME_LENGTH 50
#define MUTATION_RATE 0.1
#define CROSSOVER_RATE 0.7
#define ITERATORTIME 2000
//
#define START_X 1
#define START_Y 0
#define FINAL_X 11
#define FINAL_Y 12
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

typedef struct Individual{
    double  fitness;
    short chromosome[CHROMOSOME_LENGTH];
    double select_rate;
}individual;
individual indivs[POP_SIZE];
double sumfitness = 0;

void Mutation();
void PrintPopulation(int epoch);
void Evaluate_Individual(individual* indiv);
void Evaluate_Population();
void Crossover();
individual SelectIndividual();
void InitPop();


int main()
{
    InitPop();
    int epoch = 0 ;
    while (epoch<ITERATORTIME)
    {
        Evaluate_Population();
        PrintPopulation(epoch);
        Crossover();
        Mutation();
        epoch++;
    }
    return 0;
}

void InitPop() {
    for (int i = 0; i <POP_SIZE ; ++i) {
        for (int j = 0; j <CHROMOSOME_LENGTH ; ++j) {
            indivs[i].chromosome[j]=(short)rand()%4;
        }
        indivs[i].fitness=0;
        indivs[i].select_rate=0;
    }
}


void Crossover() {
    individual new_pop[POP_SIZE];
    int new_pop_cnt=0;
    while (new_pop_cnt<POP_SIZE-1)
    {
        individual indiv1 = SelectIndividual();
        individual indiv2 = SelectIndividual();
        double d = rand()/(double)RAND_MAX;
        //基因交换
        if (d < CROSSOVER_RATE) {
            int crosspoint=rand()%CHROMOSOME_LENGTH;
            if (crosspoint==0)
                crosspoint = 1;

            for (int i = 0; i <=crosspoint; ++i) {
                new_pop[new_pop_cnt].chromosome[i]=indiv1.chromosome[i];
                new_pop[new_pop_cnt+1].chromosome[i]=indiv2.chromosome[i];
            }
            for (int i = crosspoint+1; i <CHROMOSOME_LENGTH ; ++i) {
                new_pop[new_pop_cnt].chromosome[i]=indiv2.chromosome[i];
                new_pop[new_pop_cnt+1].chromosome[i]=indiv1.chromosome[i];
            }
        }
        //直接继承
        else{
            for (int i = 0; i <CHROMOSOME_LENGTH; ++i) {
                new_pop[new_pop_cnt].chromosome[i]=indiv1.chromosome[i];
                new_pop[new_pop_cnt+1].chromosome[i]=indiv2.chromosome[i];
            }
        }
        new_pop_cnt+=2;
    }
    for (int i = 0; i < POP_SIZE; ++i) {
        for (int j = 0; j <CHROMOSOME_LENGTH ; ++j) {
            indivs[i].chromosome[j] = new_pop[i].chromosome[j];
        }
    }
}

void Mutation() {
    for (int i = 0; i <POP_SIZE ; ++i) {
        double d = rand() /(double) RAND_MAX;
        if (d < MUTATION_RATE) {
            int mutationpos = rand()%(CHROMOSOME_LENGTH+1);
            indivs[i].chromosome[mutationpos]=rand()%4;
        }
    }
}

void PrintPopulation(int epoch) {
    individual best_indiv;
    best_indiv.fitness=0;
    printf("Generation:%d\n",epoch);
    for (int i = 0; i < POP_SIZE; ++i) {
        //打印当前染色体
        for (int j = 0; j <CHROMOSOME_LENGTH ; ++j)
            printf("%hd",indivs[i].chromosome[j]);
        printf("  fitness:%lf\n",indivs[i].fitness);

        //替换最优染色体
        if(indivs[i].fitness>best_indiv.fitness)
        {
            best_indiv = indivs[i];
        }

    }

    printf("Best Individual Path:\n");
    int flag[L][L];
    memset(flag,0, sizeof(flag));
    int pos_x=START_X,pos_y=START_Y;
    int dx,dy;
    for (int i = 0; i < CHROMOSOME_LENGTH ;++i) {
        switch (best_indiv.chromosome[i])
        {
            case UP:dx=-1;dy=0;
                break;
            case DOWN:dx=1;dy=0;
                break;
            case LEFT:dx=0;dy=-1;
                break;
            case RIGHT:dx=0;dy=1;
                break;
        }
        if (pos_x+dx>=0&&pos_x+dx<L&&pos_y+dy>=0&&pos_y+dy<L){
            if (maze[pos_x+dx][pos_y+dy]==ROUTE)
            {
                pos_x+=dx;pos_y+=dy;
                flag[pos_x][pos_y]=1;
            }
        }
    }
    for (int u = 0; u < L; ++u) {
        for (int k = 0; k <L ; ++k) {
            if (maze[u][k]==WALL) printf("#");
            else if (maze[u][k]==ROUTE)
            {
                if (flag[u][k]==1) printf("*");
                else printf(" ");
            }
        }
        printf("\n");
    }
    printf("Best Fitness:%lf",best_indiv.fitness);
    printf("\n");
    printf("\n");

}

void Evaluate_Individual(individual* indiv) {
    bool tempflag = 0;
    int step_cnt=0;
    int pos_x=START_X,pos_y=START_Y;
    for (int j = 0; j <CHROMOSOME_LENGTH; ++j) {
        int dx, dy;
        switch (indiv->chromosome[j]) {
            case UP:
                dx = -1;
                dy = 0;
                break;
            case DOWN:
                dx = 1;
                dy = 0;
                break;
            case LEFT:
                dx = 0;
                dy = -1;
                break;
            case RIGHT:
                dx = 0;
                dy = 1;
                break;
        }
        if (pos_x + dx >= 0 && pos_x + dx < L && pos_y + dy >= 0 && pos_y + dy < L) {
            if (maze[pos_x + dx][pos_y + dy] == ROUTE) {
                pos_x += dx;
                pos_y += dy;
                step_cnt++;
            }
        }
        if (pos_x == FINAL_X && pos_y == FINAL_Y) {
            double tempnumber =(double) (CHROMOSOME_LENGTH-(double)step_cnt)/CHROMOSOME_LENGTH;
            indiv->fitness =1 +tempnumber;
            tempflag = 1;
            break;
        }
    }
    if(tempflag==0)
    {
        indiv->fitness=1.0/(abs(FINAL_X-pos_x)+abs(FINAL_Y-pos_y)+1);
    }

}

void Evaluate_Population() {
    sumfitness = 0;

    for (int i=0; i<POP_SIZE; ++i) {
         Evaluate_Individual(&indivs[i]);
        sumfitness+=indivs[i].fitness;
    }
    for (int i = 0; i < POP_SIZE; ++i) {
        indivs[i].select_rate = indivs[i].fitness/sumfitness;
    }
}

individual SelectIndividual() {
    double d = rand()/(double)RAND_MAX;
    double sumrate = 0;
    for (int i = 0; i <POP_SIZE ; ++i) {
        if (d>sumrate&&d<indivs[i].select_rate+sumrate){
            return indivs[i];
        } else{
            sumrate+=indivs[i].select_rate;
        }
    }
    printf("Something Wrong !");
}