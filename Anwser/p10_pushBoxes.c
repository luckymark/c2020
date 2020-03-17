/*
Please use up, down, left, right click to control the movement of character "T"
You can't cross the barrier and push boxes aganist the barrier
You can push boxes from one side to the oppsite side 
Victory comes when you move all the boxes "O" onto "_"
Besides you can press "Esc" to quit this game
*/ 


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>

#define MAX 10
#define WIDTH 20
#define HEIGHT 10

char map[HEIGHT+5][WIDTH+5];
int mov_T[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
int location_x,location_y;
int box_x,box_y,box_num;
int aim_x,aim_y;
int now[HEIGHT+5][WIDTH+5];
int step;
FILE *fpRead;
FILE *fpWrite;

void status(int x,int y)
{
    if(x==location_x && y==location_y)
    {
        printf("T");return;
    }
    if(now[x][y]==2 || now[x][y]==5)
    {
        printf("O");return;
    }
    if(now[x][y]==3)
    {
        printf("_");return;
    }
    printf("%c",map[x][y]);
}

void print()
{
    system("CLS");
    printf("press ESE to quit\n");
    printf("Your step is %d\n",step);
    int i,j;
    for(i=0;i<=HEIGHT-1;i++)
    {
        for(j=0;j<=WIDTH-1;j++)
            status(i,j);
        printf("\n");
    }
}
int init(int x,int y)
{
    if(x>=HEIGHT || x<0 || y>=WIDTH || y<0)  return 0;
    return 1;
}
int sucess(int move)
{
    int x=location_x+mov_T[move][0];
    int y=location_y+mov_T[move][1];
    if(init(x,y)==0)   return 0;
    int x1=x+mov_T[move][0];
    int y1=y+mov_T[move][1];
    if(now[x][y]==0 || now[x][y]==3)  return 1;
    if(now[x][y]==1)  return 0;
    if(init(x1,y1) && ( now[x1][y1]==0 || now[x1][y1]==3))  return 1;
    return 0;
}
void Gaming(int move)
{
    if(move==4)  return;

    if(sucess(move))
    {
        step++;
        int x=location_x+mov_T[move][0];
        int y=location_y+mov_T[move][1];
        int x1=x+mov_T[move][0];
        int y1=y+mov_T[move][1];
        switch(now[x][y])
        {
            case 0:
                location_x=x;
                location_y=y;
                break;
            case 2:
                if(now[x1][y1]==0)
                {
                    now[x1][y1]=2;
                    now[x][y]=0;
                    location_x=x;
                    location_y=y;
                }
                else
                {
                    now[x1][y1]=5;
                    now[x][y]=0;
                    location_x=x;
                    location_y=y;
                }
                break;
            case 3:
                location_x=x;
                location_y=y;
                break;
            default:
                now[x1][y1]=2;
                now[x][y]=3;
                location_x=x;
                location_y=y;
                break;
        }
        print();
    }
}

void cin()
{
	char p;
	while(1)
	{
		fscanf(fpRead,"%c",&p);
		if(p=='\n')  break;
	}
	
    int i,j;
    memset(now,0,sizeof(now));
    for(i=0;i<HEIGHT;i++)
    {
    	for(j=0;j<WIDTH;j++)
    	{
    		char w;
    		while(1)
    		{
    			fscanf(fpRead,"%c",&w);
    			if(w!='\n') break;
			}
    		map[i][j]=w;
		}
        	
        for(j=0;j<WIDTH;j++)
            if(map[i][j]=='*')   now[i][j]=1;
    }
    fscanf(fpRead,"%d",&location_x);
    fscanf(fpRead,"%d",&location_y);
    fscanf(fpRead,"%d",&box_num);
    for(i=1;i<=box_num;i++)
    {
        fscanf(fpRead,"%d%d",&box_x,&box_y);
        now[box_x][box_y]=2;
    }
    for(i=1;i<=box_num;i++)
    {
        fscanf(fpRead,"%d%d",&aim_x,&aim_y);
        now[aim_x][aim_y]=3;
    }
}
int main()
{
    fpRead=fopen("data_in.txt","r");
   fpWrite=fopen("data_out.txt","w");
    int j=0;
    int flag;
    int Ese=0;
    for(j=1;j<=3;j++)
    {
        step=0;
        cin();
        print();
        
        while(1)
		{
        int move_press;
        int flag=0;
        int move;
        while( (move_press=getch())!=0x1B )
        {
            switch(move_press)
            {
                case 0xE0:
                    switch (move_press=getch())
                    {
                        case 72:
                            move=0;break;
                        case 80:
                            move=1;break;
                        case 75:
                            move=2;break;
                        case 77:
                            move=3;break;
                        default:
                            move=0;break;
                    }
                    break;
                default:
                    move=4;
                    break;
            }
            Gaming(move);
            if(step>500)
            {
                printf("You Lost!");
                fclose(fpRead);
                fclose(fpWrite);
                return 0;
            }
            flag=0;
            int x,y;
            for(x=0;x<HEIGHT;x++)
            {
                for(y=0;y<WIDTH;y++)
                    if(now[x][y]==2)
                    {
                        flag=1;break;
                    }
            }
            if(!flag)
            {
                fprintf(fpWrite,"You use %d step to finish the level %d\n",step,j);
                break;
            }
        }
        	if(!flag)  break;
    	}
    }
    fclose(fpRead);
    fclose(fpWrite);
    return 0;
}
