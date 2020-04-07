/*symple*/
#include<stdio.h>
#include<string.h>
void encryption( char * st, int n ){
	for( int i = 0; i < n; i ++ ){
		if( st[i] >= 'A' && st[i] <= 'Z' ){
			st[i] = st[i] + 8;
			if( st[i] > 'Z' ) st[i] = st[i] % 'Z' + 'A'; 
		}
		if( st[i] >= 'a' && st[i] <= 'z' ){
			st[i] = st[i] + 4;
			if( st[i] > 'z' ) st[i] = st[i] % 'z' + 'a'; 
		}
	}
}
void decrypt( char * st, int n ){
	for( int i = 0; i < n; i ++ ){
		if( st[i] >= 'A' && st[i] <= 'Z' ){
			st[i] = st[i] - 8;
			if( st[i] < 'A' ) st[i] = (st[i]+26) % 'Z' + 'A'; 
		}
		if( st[i] >= 'a' && st[i] <= 'z' ){
			st[i] = st[i] - 4;
			if( st[i] < 'a' ) st[i] = (st[i]+26) % 'z' + 'a'; 
		}
	}
}
char s[25]; int len;
int main(){
	scanf( "%s", s );
	len = strlen( s );
	encryption( s, len );
	printf( "%s\n", s );
	decrypt( s, len );
	printf( "%s\n", s );
	return 0;
}
