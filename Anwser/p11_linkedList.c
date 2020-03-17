#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 5000
#define NUM 3000

struct data
{
    int to,value;
};
struct data point[MAX];
int now=0,to;

void reveal(int last,int now)
{
    int to=point[now].to;
    point[now].to=last;
    if(to==-1)  return;
    reveal(now,to);
}
void init()
{
	int i,j;

    for(i=0;i<NUM-1;i++)
        point[i].to=i+1;
    point[NUM-1].to=-1;

    
    while(now>=0)
    {
        point[now].value=rand()%100;
        now=point[now].to;
    }

    to=point[0].to;
    point[0].to=-1;
 } 
void Find_first()
{
	now=NUM-1;
    int flag=0;
    while(now>=0)
    {
        if(point[now].value==5)
        {
            printf("%d\n",now);
            now=point[now].to;
            flag=1;
            break;
        }
        now=point[now].to;
    }
    if(!flag)  printf("-1\n");
}
void Find_second()
{
 	int flag=0;
    while(now>=0)
    {
        if(point[now].value==5)
        {
            printf("%d\n",now);
            now=point[now].to;
            flag=1;
            break;
        }
        now=point[now].to;
    }
    if(!flag)  printf("-1\n");	
}
int main()
{
	init();
    reveal(0,to);

    Find_first();

    Find_second();
    return 0;
}
