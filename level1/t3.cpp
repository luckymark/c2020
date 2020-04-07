#include <stdio.h>
int main(){
	for( int i = 1; ; i++ ){
		if( i * 1.0 / 6 + i * 1.0 / 12 + i * 1.0 / 7 + 5 + 4 == i * 1.0 / 2 ){
			printf("%d\n",i);
			break;
		}
	}
	return 0;
}
