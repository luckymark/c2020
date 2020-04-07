#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
int main(){
	int x = 0, flag = -1; char s[25];
	scanf( "%s", s );
	while( 1 ){
		Sleep(200);
		system( "cls" );
		if( x == 10 || x == 0 ) flag = -flag;
		for( int i = 1; i <= x; i ++ ) printf(" ");
		printf( "%s", s );
		x += flag;
	}
	return 0;
}
