#include<stdio.h>
#include<string.h>
void move( char x, char y ){ printf( "%c -> %c\n", x, y ); }
void hanoi( int n, char a , char b, char c ){
	if( n == 1 ) move( a, c );
	else{
		hanoi( n - 1, a , c, b );
		move( a, c );
		hanoi( n - 1, b, a, c );
	}
}
int n;
int main(){
	scanf( "%d", &n );
	hanoi(n,'A','B','C');
	return 0;
}
