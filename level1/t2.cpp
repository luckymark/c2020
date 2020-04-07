#include<stdio.h>
const int N = 10000005;
bool isnot[N], mark[N];
int pri[N], phi[N], tot = 0;
void init( int n ){
	isnot[1] = true; phi[1] = 1;
	for( int i = 2; i <= n; i ++ ){
		if( !isnot[i] ){ phi[i] = i - 1; pri[++tot] = i; }
		for( int t = 1; t <= tot; t ++ ){
			int j = pri[t] * i; if( j > n ) break; isnot[j] = true;
			if( i % pri[t] ) phi[j] = phi[i] * phi[pri[t]];
			else { phi[j] = pri[t] * phi[i]; break; }
		}
	}
}
int n;
int main(){
	init(1000005);
	while( 1 ){
		scanf( "%d", &n );
		if( !isnot[n] ) puts("YES");
		else puts("NAIVE!");
	}
	return 0;
}
