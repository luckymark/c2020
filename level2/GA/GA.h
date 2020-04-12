#ifndef GA_H
#define GA_H
#include<iostream>
#include<vector>
#include<random>
#include<ctime>
//函数驼峰，变量下划线
using namespace std;

default_random_engine e;

int RandNum(int first, int last)
{
	static default_random_engine e;
	static int i_num = 0;
	if (i_num == 0)
		e.seed(time(NULL));
	uniform_int_distribution<int> u(first, last);
	i_num++;
	return u(e);
}

double RandDouble(double f, double l)
{
	static default_random_engine e;
	static int i_double = 0;
	if (i_double == 0)
		e.seed(time(NULL));
	uniform_real_distribution<double> u(f, l);
	i_double++;
	return u(e);
}

struct Genome {
	vector<int> bits;
	double fit_score;
	Genome() :fit_score(0) {}
	Genome(int bit_nums) :fit_score(0) { for (int i = 0; i < bit_nums; i++) bits.push_back(RandNum(0, 1)); }
};

class GA {
private:
	int times1,times2;
	int map[13][13];
	vector<Genome> vec_genomes;
	int pop_size;
	double cross_rate, mutation_rate;
	int genome_length;
	int chromo_length;
	int fittest_genome;
	double best_score, total_score;
	int generation;
	void Mutate(vector<int>& bits);
	void Crossover(vector<int>& dad, vector<int>& mum, vector<int>& baby1, vector<int>& baby2);
	Genome& Roulette();
	void UpdateScore();
	void CreatePopulation();
	vector<int> BeToInt(vector<int>& bits);
	double TestScore(vector<int>& bits);
	void DrawRoute(vector<int>& bits);
public:
	GA(int p_size, int g_len, int ch_len, double c_rate, double m_rate, int m[13][13])
		:pop_size(p_size), cross_rate(c_rate), mutation_rate(m_rate), genome_length(g_len), chromo_length(ch_len), generation(0),total_score(0.0),times1(0),times2(0)
	{
		for (int i = 0; i < 13; i++)
			for (int j = 0; j < 13; j++)
				map[i][j] = m[i][j];
		CreatePopulation();
	}
	void Epoch();
	void ShowInformaioin();
	int Generations() { return generation; }
	int BestScore() { return best_score; }
	void DoEpoch()
	{
		while (times2<1000)
		{
			Epoch();
			if (generation%500 == 0)
				ShowInformaioin();
		}
		ShowInformaioin();
	}
	vector<int>& BestGenome() { return vec_genomes[fittest_genome].bits; }
};

void GA::Mutate(vector<int>& bits)
{
	for (int i = 0; i < bits.size(); i++)
		if (RandDouble(0, 1) < mutation_rate)
			bits[i] = !bits[i];
}

void GA::Crossover(vector<int>& dad, vector<int>& mum, vector<int>& baby1, vector<int>& baby2)
{
	if (RandDouble(0, 1) > cross_rate || mum == dad)
	{
		baby1 = mum;
		baby2 = dad;
		return;
	}
	int cp = RandNum(0, dad.size() - 1);			//头到尾Crossover Point
	for (int i = 0; i < cp; i++)
	{
		baby1.push_back(dad[i]);
		baby2.push_back(mum[i]);
	}
	for (int i = cp; i < dad.size(); i++)
	{
		baby1.push_back(mum[i]);
		baby2.push_back(dad[i]);
	}
	return;
}

Genome& GA::Roulette()//在epoch计算适应性总分
{
	double lucky = RandDouble(0, 1) * total_score;
	double now_score = 0;
	for (int i = 0; i < pop_size; i++)
	{
		now_score += vec_genomes[i].fit_score;
		if (now_score >= lucky)
			return vec_genomes[i];
	}
}

vector<int> GA::BeToInt(vector<int>& bits)
{
	vector<int> direction;
	for (int i = 0; i < bits.size(); i += 2)
	{
		if (0 == bits[i] && 0 == bits[i + 1])
			direction.push_back(0);
		else if (0 == bits[i] && 1 == bits[i + 1])
			direction.push_back(1);
		else if (1 == bits[i] && 0 == bits[i + 1])
			direction.push_back(2);
		else if (1 == bits[i] && 1 == bits[i + 1])
			direction.push_back(3);
	}
	return direction;
}

double GA::TestScore(vector<int>& bits)
{
	int tem_map[13][13];
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 13; j++)
			tem_map[i][j] = map[i][j];
	int end_x = 1, end_y = 1;			//由地图修改
	int step = 0;
	vector<int> direction = BeToInt(bits);
	for (int i = 0; i < direction.size(); i++)
	{
		switch (direction[i])
		{
		default:break;
		case 0://上
			if (tem_map[end_x - 1][end_y] != -1)
				end_x--;
			break;
		case 1://下
			if (tem_map[end_x + 1][end_y] != -1)
				end_x++;
			break;
		case 2://左
			if (tem_map[end_x][end_y - 1] != -1)
				end_y--;
			break;
		case 3://右
			if (tem_map[end_x][end_y + 1] != -1)
				end_y++;
			break;
		}
		step++;
		if (end_x == 11 && end_y == 12)
			break;
	}
	
	int sc_x = abs(end_x - 11);
	int sc_y = abs(end_y - 12);
	double s2 = 0.5 * (1 - (double)step / 31);
	double score = 0.5 / (double)(sc_x + sc_y + 1) + s2;
	return score;
}

void GA::UpdateScore()
{
	for (int i = 0; i < pop_size; i++)
	{
		vec_genomes[i].fit_score = TestScore(vec_genomes[i].bits);	
		total_score += vec_genomes[i].fit_score;  
		if (best_score - vec_genomes[i].fit_score < 0)
		{
			best_score = vec_genomes[i].fit_score;
			fittest_genome = i;
			times1++;
			break;
		}
	}
}

void GA::Epoch()
{
	UpdateScore();
	vector<Genome> babys;
	int new_baby;
	for (int i = 0; i < pop_size; i += 2)
	{
		Genome dad = Roulette();
		Genome mum = Roulette();
		Genome baby1, baby2;
		Crossover(dad.bits, mum.bits, baby1.bits, baby2.bits);
		Mutate(baby1.bits);
		Mutate(baby2.bits);
		babys.push_back(baby1);
		babys.push_back(baby2);
	}
	if (best_score != 1)
		vec_genomes = babys;
	if (times1 == 0)
		times2++;
	times1 = 0;
	total_score = 0;
	generation++;
}

void GA::CreatePopulation()
{
	for (int i = 0; i < pop_size; i++)
		vec_genomes.push_back(Genome(chromo_length));
}

void GA::DrawRoute(vector<int>& bits)//-1墙，0空，1足
{
	int tem_map[13][13];
	for (int i = 0; i < 13; i++)
		for (int j = 0; j < 13; j++)
			tem_map[i][j] = map[i][j];
	int end_x = 1, end_y = 1;			//由地图修改
	vector<int> direction = BeToInt(bits);
	for (int i = 0; i < direction.size(); i++)
	{
		switch (direction[i])
		{
		default:break;
		case 0://上
			if (tem_map[end_x - 1][end_y] != -1)
			{
				tem_map[end_x - 1][end_y] = 1;
				end_x--;
			}
			break;
		case 1://下
			if (tem_map[end_x + 1][end_y] != -1)
			{
				tem_map[end_x + 1][end_y] = 1;
				end_x++;
			}
			break;
		case 2://左
			if (tem_map[end_x][end_y - 1] != -1)
			{
				tem_map[end_x][end_y - 1] = 1;
				end_y--;
			}
			break;
		case 3://右
			if (tem_map[end_x][end_y + 1] != -1)
			{
				//tem_map[end_x][end_y] = !tem_map[end_x][end_y];
				//tem_map[end_x][end_y + 1] = !tem_map[end_x][end_y + 1];
				tem_map[end_x][end_y + 1] = 1;
				end_y++;
			}
			break;
		}
	}
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
			if (tem_map[i][j] == -1)
				cout << "▉";
			else if (tem_map[i][j] == 0)
				cout << "  ";
			else
				cout << "※";
		cout << endl;
	}
}

void GA::ShowInformaioin()
{
	cout << "现在的代数：" << generation << " " << "最佳分数：" << best_score << endl;
	DrawRoute(vec_genomes[fittest_genome].bits);
}
#endif // !GA_H