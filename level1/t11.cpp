#include<stdio.h>
const int N = 10005;
int next[N][2], flag, begin[2], n, q, id, opt, a[N];
int main(){
	scanf( "%d%d", &n, &q );
	for( int i = 1; i <= n; i++ ) scanf( "%d", &a[++id] );
	for( int i = 1; i <= n; i++ ) next[i][0] = i - 1, next[i][1] = i + 1;
	next[1][0] = -1; next[n][1] = -1; begin[0] = 1; begin[1] = n;
	int now = begin[flag];
	while( q -- ){
		scanf( "%d", &opt );
		if( opt == 1 ){//reverse
			flag ^= 1;
		}
		if( opt == 2 ){
			while( a[now] ^ 5 ) now = next[now][flag^1];
			printf( "%d\n", now );
			now = next[now][flag^1];
		}
	}
	return 0;
}
