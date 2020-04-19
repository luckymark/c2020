#include <stdio.h>
#include <stdlib.h>
#define LEVEL 		2
#define Y 			2
#define DEST 		3
#define ENTER		13
#define MAPSIZE     20


int wrong=0;
int size[LEVEL][2]={{7,7},{15,17}};
int beginning[LEVEL][2]={{1,1},{1,0}};
int wall[LEVEL][MAPSIZE][MAPSIZE]={             // 3 is destination
        {
            {0,0,0,0,0,0,0},
            {0,Y,1,1,1,1,0},
            {0,0,0,0,0,1,0},
            {0,1,1,1,1,1,0},
            {0,0,0,1,0,0,0},
			{0,1,1,1,1,3,0},
            {0,0,0,0,0,0,0}
        },
        {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0},
            {Y,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0},
            {0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,0,0},
            {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
            {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
            {0,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,0},
            {0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0},
            {0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0},
            {0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,1,0},
            {0,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,0},
            {0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0},
            {0,1,1,1,0,1,1,1,0,1,1,1,1,1,0,1,0},
            {0,1,0,1,0,1,0,1,0,0,0,0,0,1,0,1,0},
            {0,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        }
};

void pause();
void begin(int lev);
int move(int *x,int *y,int derection,int lev);
void printer(int lev);

int main()
{
    printf("  the rule:  \n  w is wall  \n  blank is road  \n  Y is you  \n  D is your destination  \n");
    printf("  press W A S D on your keyboard to move  \n\n");
    printf("  Reminder:please play in English  \n\n");
    printf("  press ENTER on your keyboard to start  \n\n\n\n  ");
    pause();

    int i;
    for(i=1;i<=LEVEL;i++)
    {
        system("cls");
		printf("\n  press ENTER on your keyboard to begin level %d  \n\n\n\n  ",i);
        pause();

        begin(i-1);
        
        
        printf("\nYou win!!!  \n\n\n  ");
        printf("press ENTER on your keyboard to come to next level  \n\n\n\n  ");
        pause();
    }
	system("cls");
    printf("\n\n  CONGRATULATION : You have pass all levels!!!  \n\n\n\n  ");
    pause();

    return 0;
}

void begin(int lev)
{
    int y[2]={beginning[lev][0],beginning[lev][1]};
    printer(lev);

    char ch;
	while(ch=getch())
	{
		if(move(&y[0],&y[1],ch,lev))
		{
			printer(lev);
			break;
		}	
		printer(lev);
	}
}

int move(int *x,int *y,int derection,int lev)
{
    int ax=*x,ay=*y;
    switch (derection)
    {
        case 'w':
        case 'W':
            ax--;
            break;
        case 's':
        case 'S':
            ax++;
            break;
        case 'a':
        case 'A':
            ay--;
            break;
        case 'd':
        case 'D':
            ay++;
            break;
    }
    switch (wall[lev][ax][ay])
    {
        case 0:
            wrong=1;
            break;
        case 1:
        	wall[lev][ax][ay]=2;
        	wall[lev][*x][*y]=1;
            *x=ax;
            *y=ay;
            break;
        case DEST:
        	wall[lev][ax][ay]=2;
        	wall[lev][*x][*y]=1;
            *x=ax;
            *y=ay;
            return 1;
    }
    return 0;
}

void printer(int lev)
{
	system("cls");
	printf("LEVEL %d\n\n",lev+1);
	int i;
	for(i=0;i<size[lev][0];i++)
	{
		int j;
		for(j=0;j<size[lev][1];j++)
			switch(wall[lev][i][j])
			{
				case 0: 
					printf("w ");
					break;
				case 1: 
					printf("  ");
					break;
				case 2: 
					printf("Y ");
					break;
				case 3: 
					printf("D ");
					break;
			}
		printf("\n");
	}
	if(wrong)
	{
		printf("\n\nThis is wall, you can't go here!  \n  ");
		wrong=0;
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
