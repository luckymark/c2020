#include<stdio.h>
const int N = 105;
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
	init( 100 );
	int b, c;
	for( int i = 6; i <= 100; i += 2 ){
		for( int j = 1; j <= tot; j ++ )
			if( !isnot[pri[j]] && !isnot[i - pri[j]] ){
				b = pri[j], c = i - pri[j];
				break;
			}
		printf( "%d = %d + %d\n", i, b, c );
	}
	return 0;
}
