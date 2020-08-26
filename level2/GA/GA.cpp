#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
const int maxn              = 50;
const int max_gen           = 1000;
const int max_chro          = 1000;
const int total_chro        = 500;
const int max_Epoch         = 500;
const int Enter_x           = 1;
const int Enter_y           = 2;
const int Exit_x            = 10;
const int Exit_y            = 29;
const double crossover_rate = 0.7;
const double mutation_rate  = 0.09;

int Rand(long long n)
	{
		int result = 0;
		for(int i = 0;i < 5;i++)
		result = ((result << 10) +rand()%1024) % n;
		return result;
	}
double Rand_1()
{
 	   return Rand(1e6) / (1e6);
}


int mp[maxn][maxn];
int n,m;
int dir[4][2]={{-1, 0}, {1, 0}, {0, -1}, {0, 1}};


int genlen = 950;
struct sel_pair{
	int chro_1,chro_2;
};

struct individual
{
	bool gen[max_gen];
	int end_x,end_y,step;
	double fitness, score;
	void get_gen()
	{
		for(int i = 0;i < genlen;i++)
		gen[i] = rand()%2;
	}
	void get_score()
	{
		int pos_x, pos_y;
		step = 0;
		
		pos_x = Enter_x;
		pos_y = Enter_y;
		for(int i = 0;i < genlen;i += 2)
		{
			int d = (gen[i] << 1)  + gen[i + 1];
			if(mp[pos_x + dir[d][0]][pos_y + dir[d][1]] == 0)
			{
				pos_x = pos_x + dir[d][0];
				pos_y = pos_y + dir[d][1];
				step++;
			}
			if(pos_x == Exit_x && pos_y == Exit_y) break;
		}
		end_x = pos_x,end_y = pos_y;
		score = 1.0 / ((Exit_x + Exit_y - (pos_x + pos_y) + 1) * 500 + step);
	}
	void mutation()
	{
		for(int i = 0;i < genlen;i++)
		{
			double rd = Rand_1(); 
			if(rd < mutation_rate)
			gen[i] ^= 1;
		}
	}
};

struct population{
	individual chromosome[max_chro];
	void creat_init_generation()
	{
		for(int i = 0;i < total_chro;i++)
		{
			chromosome[i].get_gen();
			chromosome[i].get_score();
		}
	}
	void random_shuffle(int (&a)[total_chro])
	{
		for(int i = 0;i < total_chro;i++)
		a[i] = i;
		for(int i = 1;i < total_chro;i++)
		{
			int rd = Rand(i);
			a[i] ^= a[rd];
			a[rd] ^= a[i];
			a[i] ^= a[rd];
		}
	}
	 
	int roulette_wheel_selection()
	{
		int a[total_chro];
		random_shuffle(a);
		double rd = Rand_1(), total_fitness = 0.0;
		for(int i = 0;i < total_chro;i++)
		{
			total_fitness += chromosome[i].fitness;
			if(total_fitness >= rd)
			return i;
		}
		return total_chro - 1;
		
	}
	sel_pair selection()
	{
		double total_score = 0.0;
		sel_pair cp;
		for(int i = 0;i < total_chro;i++)
		total_score += chromosome[i].score;
		for(int i = 0;i < total_chro;i++)
		chromosome[i].fitness = chromosome[i].score / total_score;
		cp.chro_1 = roulette_wheel_selection();
		cp.chro_2 = roulette_wheel_selection();
		return cp;
	}
	void crossover(sel_pair &son)
	{
		double rd = Rand_1();
		if(rd < crossover_rate)
		{
			int pos = Rand(genlen);
			for(int  i = pos;i < genlen;i++)
			{
				chromosome[son.chro_1].gen[i] ^= chromosome[son.chro_2].gen[i];
				chromosome[son.chro_2].gen[i] ^= chromosome[son.chro_1].gen[i];
				chromosome[son.chro_1].gen[i] ^= chromosome[son.chro_2].gen[i];
			}
		}
	}
}; 

void load_mp()
{
	FILE *fin;
	fin = fopen("map_data.txt", "r");
	fscanf(fin,"%d%d",&n,&m);
	for(int i = 1;i <= n;i++)
	for(int j = 1;j <= m;j++)
	{
		fscanf(fin,"%d", &mp[i][j]);
	}
}
void GA()
{
	int Epoch = 0;
	int pos_x, pos_y;
	population A,B;
	A.creat_init_generation();
	while(Epoch < max_Epoch)
	{
		for(int i = 0;i < total_chro;i++)
		{
			sel_pair cp = A.selection();
			B.chromosome[i] = A.chromosome[cp.chro_1];
			B.chromosome[i + 1] = A.chromosome[cp.chro_2];
			cp.chro_1 = i;
			cp.chro_2 = i + 1;
			B.crossover(cp);
			B.chromosome[i].mutation();
			B.chromosome[i].get_score();
			B.chromosome[i + 1].mutation();
			B.chromosome[i + 1].get_score();
		}
		A = B;
		Epoch++;
	}
	int pos = 0;
	for(int i = 1;i < total_chro;i++)
	if(A.chromosome[i].score > A.chromosome[pos].score)
	pos = i;
	FILE *fout;
	fout = fopen("step.txt","w");
	pos_x = Enter_x;
	pos_y = Enter_y;
	for(int i = 0;i < genlen;i += 2)
	{
		int d = (A.chromosome[pos].gen[i] << 1) +  A.chromosome[pos].gen[i + 1];
		if(mp[pos_x + dir[d][0]][pos_y + dir[d][1]] == 0)
		{
				pos_x = pos_x + dir[d][0];
				pos_y = pos_y + dir[d][1];
		}
		else continue;
		if(d == 0) fprintf(fout,"up\n");
		else if(d == 1) fprintf(fout,"down\n");
		else if(d == 2) fprintf(fout,"left\n");
		else if(d == 3) fprintf(fout,"right\n");
	}
	fprintf(fout,"step = %d\n",A.chromosome[pos].step);
}

int main(void)
{
	srand(time(0));
	memset(mp,-1,sizeof(mp));
	load_mp();
	GA();
	return 0;
}


