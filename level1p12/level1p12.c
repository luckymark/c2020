#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define MAXTYPE 1000
#define MAXNUM 1000
#define MAXID 1000
struct good
{
	int id,wei;
}g[MAXTYPE],tmp;
int ids[MAXID];
int type,wei;
void print()
{
	system("cls");
	printf("Total good types:%d,total good nums:%dkg\n",type,wei);
	for(int i=1;i<=type;i++)
		printf("%d:%dkg\n",g[i].id,g[i].wei);
	puts("--------------------");
	char ch;
	puts("PRESS e TO GO TO MENU");
	while(ch=getch())
	{
		if(ch=='e'||ch=='E')return;
	}
}
void add()
{
	system("cls");
	FILE *fp=fopen("good.txt","w");
	puts("INPUT THE GOOD ID");
	scanf("%d",&tmp.id);
	if(!ids[tmp.id])ids[tmp.id]=++type;
	puts("INPUT THE GOOD WEIGHT(INTEGER)");
	scanf("%d",&tmp.wei),wei+=tmp.wei,tmp.wei+=g[ids[tmp.id]].wei;
	g[ids[tmp.id]]=tmp;
	fprintf(fp,"Total good types:%d,total good nums:%dkg\n",type,wei);
	for(int i=1;i<=type;i++)
		fprintf(fp,"%d:%dkg\n",g[i].id,g[i].wei);
	fclose(fp);
}
void minus()
{
	if(type==0)
	{
		char ch;
		puts("THERE IS NO GOOD IN STORAGE");
		puts("PRESS e TO GO TO MENU");
		while(ch=getch())
		{
			if(ch=='e'||ch=='E')return;
		}
	}
	FILE *fp=fopen("good.txt","w");
	do
	{
		system("cls");
		puts("INPUT THE GOOD ID");
		scanf("%d",&tmp.id);
		if(!ids[tmp.id]||g[ids[tmp.id]].wei==0)puts("WRONG ID");
	}while(!ids[tmp.id]||g[ids[tmp.id]].wei==0);
	do
	{
		system("cls");
		printf("INPUT THE GOOD WEIGHT(INTEGER) LESS THAN %d\n",g[ids[tmp.id]].wei);
		scanf("%d",&tmp.wei);
		if(tmp.wei>g[ids[tmp.id]].wei)puts("OUT OF LIMIT");
	}while(tmp.wei>g[ids[tmp.id]].wei);
	g[ids[tmp.id]].wei-=tmp.wei;
	wei-=tmp.wei;
	fprintf(fp,"Total good types:%d,total good nums:%dkg\n",type,wei);
	for(int i=1;i<=type;i++)
		fprintf(fp,"%d:%dkg\n",g[i].id,g[i].wei);
	fclose(fp);
	return;
}
void init()
{
	FILE *fp=fopen("good.txt","r");
	fscanf(fp,"Total good types:%d,total good nums:%dkg\n",&type,&wei);
	for(int i=1;i<=type;i++)
		fscanf(fp,"%d:%dkg",&g[i].id,&g[i].wei),ids[g[i].id]=i;
}
void print_menu()
{
	system("cls");
	puts("INPUT NUMBERS TO REALIZE THE FUNCTION");
	puts("1.Display inventory list");
	puts("2.BUY IN");
	puts("3.SELL");
	puts("4.exit");
}
int main()
{
	init();
	char ch;
	print_menu();
	while(ch=getch())
	{
		switch(ch)
		{
			case '1':print();break;
			case '2':add();break;
			case '3':minus();break;
			case '4':exit(0);break;
		}
		print_menu();
	}
}
