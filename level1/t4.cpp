#include <stdio.h>
bool check( int x ){
	int a = x / 100, b = ( x % 100 ) / 10, c = ( x % 10 );
	return x == a * a * a + b * b * b + c * c * c; 
}
int main(){
	for( int i = 100; i <= 999; i ++ ) if( check(i) ) printf( "%d\n", i );
	return 0;
}
