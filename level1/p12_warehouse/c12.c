#include<stdio.h>
#include<stdlib.h>
#define MAX 20

typedef struct goods {
	int size;
	int amount;
	char name[MAX];
}Goods;

int read(Goods *goods){
	FILE* fp = fopen("data.txt", "r");
	int num;
	fscanf(fp, "%d",&num);
	for (int i = 0; i < num; i++)
	{
		fscanf(fp, "%d %d %20s", &goods[i].size, &goods[i].amount, goods[i].name);
	}
	fclose(fp);
	return num;
};

void view(Goods* goods,int *num) {
	printf
	(
		"欢迎使用库存系统\n"
		"1.显示存货列表\n"
		"2.入库\n"
		"3.出库\n"
		"4.退出程序\n"
	);
};

void viewStore(Goods* goods, int num) {
	printf("共有%d件货物\n", num);
	int exit = 0;
	for (int i = 0; i < num; i++)
	{
		printf(
			"第%d件货物：\n", i + 1);
		printf(
			"           名字：%s\n", goods[i].name);
		printf(
			"           数量：%d\n", goods[i].amount);
		printf(
			"           型号：%d\n", goods[i].size);

	};
	while (1) {
		printf("输入1返回主菜单\n");
		scanf("%d", &exit);
		if (exit == 1) {
			break;
		}
	}
	system("CLS");
};

void enter(Goods* goods, int *num) {
	printf("请输入要进入库存的货物名字：");
	scanf("%s",goods[*num].name);
	printf("型号：1：大号，2：中号，3：小号\n请输入要进入库存的货物型号：");
	scanf("%d", &goods[*num].size);
	printf("请输入要进入库存的货物数量：");
	scanf("%d", &goods[*num].amount);
	*num=*num+1;
	system("CLS");
};

void out(Goods* goods, int* num) {
	int outnum;
	while (1) {
		printf("请选择要第几件货物退出库存的货物：");
		scanf("%d", &outnum);
		if ((outnum -1)< (*num))
		{
			break;
		}
		else {
			printf("选择的货物不在库存中\n");
		}
		
	}
	for (int n = outnum; n < (*num); n++)
	{
		for (int i = 0; i < MAX; i++)
		{
			goods[n - 1].name[i] = goods[n].name[i];
		};

		goods[n - 1].amount = goods[n].amount;
		goods[n - 1].size = goods[n].size;
	}
	*num = (*num - 1);
	system("CLS");
};


void write(Goods* goods,int num) {
	FILE* fp = fopen("data.txt", "w");
	fprintf(fp, "%d\n", num);
	for (int i = 0; i < num; i++)
	{
		fprintf(fp, "%d %d %-20s\n", goods[i].size, goods[i].amount, goods[i].name);
	}
	fclose(fp);
};


int main() {
	Goods goods[MAX];//初始化结构
	Goods* pgoods = goods;
	int num;
	num=read(pgoods);
	while (1) {
		int chose= 0;
		int exit = 0;
		view(pgoods, &num);
		scanf("%d", &chose);
		switch (chose)
		{
		case 1:viewStore(pgoods, num); break;
		case 2:enter(pgoods, &num); break;
		case 3:out(pgoods, &num); break;
		case 4:exit = 1; break;
		default:break;
		}
		if (exit == 1)
		{
			write(pgoods, num);
			break;
		}
		system("CLS");
	};
	return 0;
}



