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
        0,1,0,0,0,1,0,0,0,0,1,0,0,
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
#define POP_SIZE 20
#define CHROMO_LENGTH 50
#define MUTATION_RATE 0.3
#define CROSSOVER_RATE 0.7
#define ITERATORTIME 300
//
#define START_X 1
#define START_Y 0
#define FINAL_X 11
#define FINAL_Y 12

typedef struct Chromosome{
    short int chromo[CHROMO_LENGTH];
    double fitness;
    double rate;
}chromosome;
chromosome pop[POP_SIZE];


void CreatePop();
void CalculateFitness();
void Crossover();
void Mutation();
int ChooseChromo();
void ReadMap();
void printpop(int epoch)
{
    chromosome best_indiv;
    best_indiv.fitness=0;
    printf("Generation:%d\n",epoch);
    for (int i = 0; i < POP_SIZE; ++i) {
        //打印当前染色体
        for (int j = 0; j <CHROMO_LENGTH ; ++j) {
            printf("%d",pop[i].chromo[j]);
        }
        printf("  fitness:%lf",pop[i].fitness);
        printf("\n");

        //替换最优染色体
        if(pop[i].fitness>best_indiv.fitness)
        {
            best_indiv.fitness=pop[i].fitness;
            for (int j = 0; j < CHROMO_LENGTH; ++j) {
                best_indiv.chromo[j]=pop[i].chromo[j];
            }
        }

    }

    printf("Best Individual Path:\n");
    memset(flag,0, sizeof(flag));
    int pos_x=START_X,pos_y=START_Y;
    int dx,dy;
    for (int i = 0; i < CHROMO_LENGTH; ++i) {
        if(best_indiv.chromo[i]==0){
            dx=-1;dy=0;
        }
        else if (best_indiv.chromo[i]==1){
            dx=1;dy=0;
        }
        else if (best_indiv.chromo[i]==2){
            dx=0;dy=-1;
        }
        else if (best_indiv.chromo[i]==3){
            dx=0;dy=1;
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
int main()
{
   // ReadMap();
    int epoch =1;
    CreatePop();
    CalculateFitness();
    printpop(1);
    while(epoch<ITERATORTIME)
    {
        epoch++;
        Crossover();
        Mutation();
        CalculateFitness();
        printpop(epoch);

    }
    getchar();
    getchar();
    return 0;
}

void ReadMap() {
    freopen("maze.txt","r",stdin);
    for (int i = 0; i <L ; ++i) {
        for (int j = 0; j <L ; ++j) {
            scanf("%d",&maze[i][j]);
        }
    }
    fclose(stdin);
}

void Mutation() {
    for (int i = 0; i <POP_SIZE ; ++i) {
        double d = rand() /(double) RAND_MAX;
        if (d < MUTATION_RATE) {
            int mutationpos = rand()%(CHROMO_LENGTH+1);
            pop[i].chromo[mutationpos]=rand()%4;
        }
    }
}

void Crossover() {
    chromosome new_pop[POP_SIZE];
    int new_pop_cnt=0;
    while (new_pop_cnt<POP_SIZE-1) {
        int indiv_1 = ChooseChromo();
        int indiv_2 = ChooseChromo();
        double d = rand()/(double)RAND_MAX;
        if (d < CROSSOVER_RATE) {
            int crosspoint = (rand() % (CHROMO_LENGTH - 1));
            short int temp;
            for (int i = crosspoint; i < CHROMO_LENGTH; ++i) {
                temp = pop[indiv_1].chromo[i];
                pop[indiv_1].chromo[i] = pop[indiv_2].chromo[i];
                pop[indiv_2].chromo[i] = temp;
            }
        }

        for (int j = 0; j < CHROMO_LENGTH; ++j) {
            new_pop[new_pop_cnt].chromo[j]=pop[indiv_1].chromo[j];
            new_pop[new_pop_cnt+1].chromo[j]=pop[indiv_2].chromo[j];
        }
        new_pop[new_pop_cnt].fitness=pop[indiv_1].fitness;
        new_pop[new_pop_cnt].rate=pop[indiv_1].rate;
        new_pop[new_pop_cnt+1].fitness=pop[indiv_2].fitness;
        new_pop[new_pop_cnt+1].rate=pop[indiv_2].rate;
        new_pop_cnt+=2;
    }

    for (int i = 0; i <POP_SIZE ; ++i) {
        for (int j = 0; j < CHROMO_LENGTH; ++j) {
            pop[i].chromo[j]=new_pop[i].chromo[j];
        }
        pop[i].fitness=new_pop[i].fitness;
        pop[i].rate=new_pop[i].rate;

    }

}

int ChooseChromo() {
    double d,sum_rate=0;
    d = rand()/(double)RAND_MAX;
    for (int i=0; i<POP_SIZE; ++i) {
        if((sum_rate+pop[i].rate)>d&&d>sum_rate){
            return i;
        }
        else{
            sum_rate+=pop[i].rate;
        }
    }
}

void CalculateFitness() {
    int pos_x=START_X,pos_y=START_Y;
    double sumfitness = 0;
    for (int i=0; i<POP_SIZE; ++i) {
        pos_x=START_X,pos_y=START_Y;
        for (int j = 0; j <CHROMO_LENGTH; ++j) {
            if(pop[i].chromo[j]==0){
                if(pos_x-1>=0){
                    if(maze[pos_x-1][pos_y]==ROUTE)
                         pos_x-=1;
                }
            }
            else if (pop[i].chromo[j]==1){
                if(pos_x+1<L){
                   if(maze[pos_x+1][pos_y]==ROUTE)
                       pos_x+=1;
                }
            }
            else if (pop[i].chromo[j]==2){
                if(pos_y-1>=0){
                    if (maze[pos_x][pos_y-1]==ROUTE)
                        pos_y-=1;
                }
            }
            else if (pop[i].chromo[j]==3){
                if(pos_y+1<L){
                    if (maze[pos_x][pos_y+1]==ROUTE)
                     pos_y+=1;
                }
            }
            if(pos_x==FINAL_X&&pos_y==FINAL_Y)
                break;
        }
        double  temp = 1.0/(abs(FINAL_X-pos_x)+abs(FINAL_Y-pos_y)+1);
        pop[i].fitness=temp;
        sumfitness += temp;

    }
    for (int i = 0; i < POP_SIZE; ++i) {
        pop[i].rate = pop[i].fitness/sumfitness;
    }

}

void CreatePop() {

    srand((unsigned)time(NULL));
    chromosome new_indiv;
    for (int i = 0; i < POP_SIZE ; ++i) {
        for (int j = 0; j <CHROMO_LENGTH ; ++j) {
            new_indiv.chromo[j]=(short)rand()%4;
        }
        new_indiv.fitness=0;
        new_indiv.rate=0;
        pop[i]=new_indiv;
    }

}
