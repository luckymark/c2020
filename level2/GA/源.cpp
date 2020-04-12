#include<iostream>
#include<vector>
#include<random>
#include<ctime>
#include<fstream>
#include"GA.h"
//函数驼峰，变量下划线

using namespace std;

int map[13][13];
void OpenFile();

int main()
{
	clock_t startTime, endTime;
	startTime = clock();
	OpenFile();
	GA bob(300, 2, 60, 0.7, 0.01, map);
	bob.DoEpoch();
	endTime = clock();
	cout << "The run time is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
	return 0;
}

void OpenFile()
{
	fstream file;
	file.open("D://maze_map1.txt");
	for(int i = 0 ; i < 13;i++)
		for (int j = 0; j < 13; j++)
		{
			file >> map[i][j];
		}
	file.close();
}
