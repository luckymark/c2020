#include<windows.h>
#include<stdio.h>
#include<ctime> 
const int MAX=30; 
const int FRAMES=24;
int main()
{
	int head=0,f=1;
	while(1)
	{
		for(int i=1;i<=head;i++) printf(" ");
		printf("x");
		Sleep(1000/FRAMES);
		head+=f;
		if(head==MAX||head==0) f=-f;
		system("cls");
	} 
}
