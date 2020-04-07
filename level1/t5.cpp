#include<stdio.h>
#include<time.h>
const int N = 1005;
bool isnot[N];
int pri[N], tot = 0;
void init( int n ){
	isnot[1] = true;
	for( int i = 2; i <= n; i ++ ){
		if( !isnot[i] ) pri[++tot] = i;
		for( int t = 1; t <= tot; t ++ ){
			int j = pri[t] * i; if( j > n ) break; 
			isnot[j] = true;
		}
	}
}
int main(){
	clock_t t1, t2; t1 = clock();
	init( 1000 );
	for( int i = 1; i <= tot; i ++ ) printf( "%d\n", pri[i] );
	t2 = clock(); printf( "time:%d\n", t2 - t1 );
	return 0;
}
