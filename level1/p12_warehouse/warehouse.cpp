#include<stdio.h>
#include<cmath>
#include<cstring>
#include<windows.h>

const int MAXN=100002;
const int NAME_LENGTH=20;

int GoodsTypes;

struct Goods
{
	char name[NAME_LENGTH];
	int num,type;
}g[MAXN];

void Clear(int posi)
{
	while(posi<GoodsTypes)
	{
		strcpy(g[posi].name,g[posi+1].name);
		g[posi].type=g[posi+1].type;
		g[posi].num=g[posi+1].num;
		posi++;
	}
	GoodsTypes--;
	return;
}
void Input()
{
	memset(g,0,sizeof(g));
	scanf("%d",&GoodsTypes);
	for(int i=1;i<=GoodsTypes;i++)
	scanf("%s %d %d",g[i].name,&g[i].type,&g[i].num);
	return;
}

void Output()
{
	freopen("goods.in","w",stdout);
	printf("%d\n",GoodsTypes);
	for(int i=1;i<=GoodsTypes;i++)
	printf("%s %d %d\n",g[i].name,g[i].type,g[i].num);
	return;
}

void Print()
{
	printf("the total type is %d\n",GoodsTypes);
	for(int i=1;i<=GoodsTypes;i++)
	printf("name:%s type:%d number:%d\n",g[i].name,g[i].type,g[i].num);
	printf("\n\n");
	Sleep(1000); 
	return;
}

void Load()
{
	char name_temp[NAME_LENGTH];//temprary
	int type_temp,num_temp;
	printf("please enter the name\n");
	scanf("%s",name_temp);
	printf("please enter the type\n");
	scanf("%d",&type_temp);
	printf("please enter the num\n");
	scanf("%d",&num_temp);
	for(int i=1;i<=GoodsTypes;i++)
	{
		if(strcmp(g[i].name,name_temp)==0&&g[i].type==type_temp)
		{
			g[i].num+=num_temp;
			printf("option has been excuted.\n\n\n");
			Sleep(1000); 
			return;
		}
	}
	GoodsTypes++;
	strcpy(g[GoodsTypes].name,name_temp);
	g[GoodsTypes].type=type_temp;
	g[GoodsTypes].num=num_temp;
	printf("option has been excuted.\n\n\n");
	Sleep(1000); 
	return ;
}
void Unload()
{
	char name_temp[NAME_LENGTH];//temprary
	int type_temp,num_temp;
	printf("please enter the name\n");
	scanf("%s",name_temp);
	printf("please enter the type\n");
	scanf("%d",&type_temp);
	printf("please enter the num\n");
	scanf("%d",&num_temp);
	for(int i=1;i<=GoodsTypes;i++)
	{
		if(strcmp(g[i].name,name_temp)==0&&g[i].type==type_temp)
		{
			if(g[i].num<num_temp) printf("There are not so many.\n\n\n");
			else 
			{
				g[i].num-=num_temp;
				if(g[i].num==0) Clear(i);
				printf("option has been excuted.\n\n\n");
			}
			Sleep(1000); 
			return;
		}
	}
	printf("there is no such kind of goods.\n\n\n");
	Sleep(1000); 
	return;
} 
int main()
{
	printf("enter 1 if you want to read from the file, 0 for other cases.\n");
	printf("(note:enter 0 if this is your first time using this software.)\n");
	int jud;
	scanf("%d",&jud);
	if(jud==1)
	{
		freopen("goods.in","r",stdin);
		Input();
		fclose(stdin);
	}
	
	freopen("CON","r",stdin);// running on windows,DOS
	//freopen("dev/tty","r",stdin)  //running on unix, linux, max os x, android
	while(1)
	{ 
		printf("-------------------------------------------------\n");
		printf("select the option\n");
		printf("0:show the current goods list.\n");
		printf("1:load goods in storage.\n");
		printf("2:unload goods from storage.\n");
		printf("3:exit the software.\n");
		scanf("%d",&jud);
		if(jud==0) Print();
		else if(jud==1) Load();
		else if(jud==2) Unload();
		else 
		{
			Output();
			return 0;
		}
	}
}
