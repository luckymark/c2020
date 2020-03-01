#include"maze.h"
int main(){
	printf("Please input filename to store maze\n");
	char buf[100];
	scanf("%s",buf);
    createMaze(buf);
}

