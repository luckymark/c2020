#include <stdio.h>
#include <stdlib.h>
#define LEVEL 		4
#define WALL 		0
#define ROAD		1
#define DEST		2
#define SIZEMAX		20
#define BOXMAX		8
#define ENTER		13

int _bestscore[LEVEL]={99999999,99999999,99999999,99999999};
int _boxnum[LEVEL]={4,3,4,5};
int _boxplace[LEVEL][BOXMAX][2]={{{2,3},{3,5},{4,2},{5,4}},{{2,2},{2,3},{3,2}},{{2,2},{3,4},{3,7},{4,6}},{{2,4},{3,3},{3,5},{4,4},{4,6}}};
int _beginning[LEVEL][2]={{3,3},{1,1},{3,2},{3,8}};
int _size[LEVEL][2]={{8,8},{9,9},{7,10},{7,10}};
int _map[LEVEL][SIZEMAX][SIZEMAX]={    
    {
        {1,1,0,0,0,1,1,1},
		{1,1,0,2,0,1,1,1},
        {1,1,0,1,0,0,0,0},
        {0,0,0,1,1,1,2,0},
        {0,2,1,1,1,0,0,0},
        {0,0,0,0,1,0,1,1},
        {1,1,1,0,2,0,1,1},
        {1,1,1,0,0,0,1,1},
    },
    {
    	{0,0,0,0,0,1,1,1,1},
    	{0,1,1,1,0,1,1,1,1},
    	{0,1,1,1,0,1,0,0,0},
    	{0,1,1,1,0,1,0,2,0},
    	{0,0,0,1,0,0,0,2,0},
    	{1,0,0,1,1,1,1,2,0},
    	{1,0,1,1,1,0,1,1,0},
    	{1,0,1,1,1,0,0,0,0},
    	{1,0,0,0,0,0,1,1,1}
	},
	{
		{1,0,0,0,0,0,0,0,1,1},
		{1,0,1,1,1,1,1,0,0,0},
		{0,0,1,0,0,0,1,1,1,0},
		{0,1,1,1,1,1,1,1,1,0},
		{0,1,2,2,0,1,1,1,0,0},
		{0,0,2,2,0,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,1}
	},
	{
		{1,1,1,0,0,0,0,0,0,1},
		{1,0,0,0,1,1,1,1,0,1},
		{0,0,2,1,1,0,0,1,0,0},
		{0,2,2,1,1,1,1,1,1,0},
		{0,2,2,1,1,1,1,1,0,0},
		{0,0,0,0,0,0,1,1,0,1},
		{1,1,1,1,1,0,0,0,0,1}
	}
};

int score;
int lev;
int iplace[2];
int boxnum;
int boxplace[BOXMAX][2];
int size[2];
int map[SIZEMAX][SIZEMAX];

void begin();
void move(int derection);
void printer();
int ifwin();
void replay();
void initializer();
void pause();
void _pause();

int main()
{
    printf("  the rule:  \n  w is wall  \n  blank is road  \n  I is you  \n  O is box\'s destination  \n  H is box  \n  V is box on destination  \n");
    
    printf("  press W A S D on your keyboard to move  \n\n");
    printf("  Reminder:please play in English  \n\n");
    printf("  press ENTER on your keyboard to start  \n\n\n\n  ");
    pause();
	
    for(lev=0;lev<LEVEL;lev++)
    {
        system("cls");
		printf("\n  press ENTER on your keyboard to begin level %d  \n\n\n\n  ",lev+1);
        pause();
        
        begin();
        
        printf("\nYou win!!!  \n  ");
        if(score<_bestscore[lev])
        {
        	_bestscore[lev]=score;
        	printer();
        	printf("\nnew record : %d !!!\n\n\n",score);
		}
		
        printf("press ENTER on your keyboard to come to next level  \n\n\n\n  ");
        _pause();
    }
	system("cls");
	
    printf("\n\n  CONGRATULATION : You have pass all levels!!!  \n\n");
    printf("  BEST RECORD  \n");
    for(lev=0;lev<LEVEL;lev++)
    	printf("    LEVEL %d  %d\n",lev+1,_bestscore[lev]);
    
    pause();
	system("cls");
    printf("\n\n\n     Thank you for palying!    \n\n\n");
    return 0;
}

void begin()
{
	initializer();
	printer();
    char ch;
	while(ch=getch())
	{
		
		move(ch);
		
		if(ifwin())
		{
			printer();
			break;
		}	
		printer();
	}
}

void printer()
{
	system("cls");
	printf("LEVEL %d  SCORE %d  BEST RECORD %d\n\n",lev+1,score,_bestscore[lev]);
	int i;
	for(i=0;i<size[0];i++)
	{
		int j,k;
		for(j=0;j<size[1];j++)
			switch(map[i][j])
			{
				case 0: 
					printf("w ");
					break;
				case 1: 
					if(iplace[0]==i&&iplace[1]==j)
					{
						printf("I ");
						break;
					}
					for(k=0;k<boxnum;k++)
					{
						if(boxplace[k][0]==i&&boxplace[k][1]==j)
						{
							k=-1;
							printf("H ");
							break;
						}
					}
					if(k>=0)
						printf("  ");
					break;
				case 2: 
					if(iplace[0]==i&&iplace[1]==j)
					{
						printf("I ");
						break;
					}
					for(k=0;k<boxnum;k++)
					{
						if(boxplace[k][0]==i&&boxplace[k][1]==j)
						{
							k=-1;
							printf("V ");
							break;
						}
					}
					if(k>=0)
						printf("O ");
					break;
			}
		printf("\n");
	}
	printf("\nYou can press R on your keyboard to replay this level  \n\n\n\n  ");
}

void move(int derection)
{
    int i;
    int x1,y1,x2,y2;
	switch (derection)
    {
        case 'w':
        case 'W':
            x1=iplace[0]-1;
            y1=iplace[1];
            x2=iplace[0]-2;
            y2=iplace[1];
            break;
        case 's':
        case 'S':
            x1=iplace[0]+1; 
            y1=iplace[1]; 
            x2=iplace[0]+2;
            y2=iplace[1];
            break;
        case 'a':
        case 'A':
            x1=iplace[0];
            y1=iplace[1]-1; 
            x2=iplace[0];
            y2=iplace[1]-2; 
            break;
        case 'd':
        case 'D':
            x1=iplace[0];
            y1=iplace[1]+1; 
            x2=iplace[0];
            y2=iplace[1]+2; 
            break;
        case 'r':
        case 'R':
        	replay();
        	break;
    }
    if(map[x1][y1])
    {
		int pushbox;
		for(i=0;i<boxnum;i++)
			if(boxplace[i][0]==x1&&boxplace[i][1]==y1)
			{
				pushbox=i;
				i=-1;
				break;
			}
		if(i>=0)
		{
			iplace[0]=x1;
			iplace[1]=y1;
			score++;
		} 	
		else
		{
			if(map[x2][y2])
			{
				for(i=0;i<boxnum;i++)
					if(boxplace[i][0]==x2&&boxplace[i][1]==y2)
					{
						i=-1;
						break;
					}
				if(i>=0)
				{
					iplace[0]=x1;
					iplace[1]=y1;
					
					boxplace[pushbox][0]=x2;
					boxplace[pushbox][1]=y2;
					score++;
				}
			}
		}
	}    
}

int ifwin()
{
	int i;
	for(i=0;i<boxnum;i++)
	{
		if(map[boxplace[i][0]][boxplace[i][1]] == 1)
			return 0;
	}
	return 1;
}

void initializer()
{
	score = 0;
	boxnum=_boxnum[lev];
	iplace[0]=_beginning[lev][0];			iplace[1]=_beginning[lev][1];
	size[0]=_size[lev][0];				size[1]=_size[lev][1];
	int i,j;
	for(i=0;i<boxnum;i++)
		for(j=0;j<2;j++)
			boxplace[i][j]=_boxplace[lev][i][j];	
	for(i=0;i<_size[lev][0];i++)
		for(j=0;j<_size[lev][1];j++)
			map[i][j]=_map[lev][i][j];
}

void replay()
{
	printf("Are you sure you want to replay this level?(Y/N)\n  ");
	char ch;
	while(1)
	{
		ch=getch();
		if(ch=='Y'||ch=='y'||ch==ENTER)
		{
			initializer();
			break;
		}
		if(ch=='w'||ch=='a'||ch=='s'||ch=='d'||ch=='W'||ch=='A'||ch=='S'||ch=='D'||ch=='n'||ch=='N')
			break;
	}
}


void pause()
{
	char ch;
	while(1)
	{
		ch=getch();
		if(ch==ENTER)
			break;
	}
}

void _pause()
{
	char ch;
	while(1)
	{
		ch=getch();
		if(ch==ENTER)
			break;
		if(ch=='r'||ch=='R')
		{
			printf("Are you sure you want to replay this level?(Y/N)\n  ");
			while(1)
			{
				ch=getch();
				if(ch=='Y'||ch=='y')
				{
					lev--;
					return;
				}
				if(ch=='n'||ch=='N')
				{
					printer();
					printf("press ENTER on your keyboard to come to next level  \n\n\n\n  ");
					_pause();
				}	
				if(ch==ENTER)
					return;
			}
		}
	}
}
