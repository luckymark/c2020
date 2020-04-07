#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<cmath>
const int N = 105;
int m, n, x1, y2;
int maze_[N][N]; char t;
int maze_print( int x, int y ){
	for( int i = 1; i <= m; i ++ ){
		for( int j = 1; j <= n; j ++ ){
			if( maze_[i][j] ){
				printf("¨€");
			} else{
				if( i == x && j == y ){
					printf("¡ï");
				} else printf("  ");
			}
		}
		puts("");
	}
}
int main(){
	FILE *mf; 
	x1 = 1, y2 = 1;
	if( ( mf = fopen( "D:\\file.txt", "r" ) ) == NULL ){
		puts("ERROR");
		exit(0);
	}
	fscanf( mf, "%d %d\n", &m, &n );//fgetc(mf);
	while( !feof( mf ) ){
		for( int i = 1; i <= m; i ++ ){
			for( int j = 1; j <= n; j ++ ){
				fscanf( mf, "%d ", &maze_[i][j] );
				//fprintf( stdout, "%d ", maze__[i][j] );
			}
			//puts("");
		}
	}
	maze_print( x1, y2 );
	do{
		t = getch();
		system("cls");
		switch( t ){
			case'w':{
				if( x1 > 1 ){
					x1--;
					maze_print( x1, y2 );
				} else{
					maze_print( x1, y2 );
				}
				break;
			}
			case's':{
				if( x1 < m ){
					x1++;
					maze_print( x1, y2 );
				} else{
					maze_print( x1, y2 );
				}
				break;
			}
			case'a':{
				if( y2 > 1 ){
					y2--;
					maze_print( x1, y2 );
				} else{
					maze_print( x1, y2 );
				}
				break;
			}
			case'd':{
				if( y2 < n ){
					y2++;
					maze_print( x1, y2 );
				} else{
					maze_print( x1, y2 );
				}
				break;
			}
			case'q':{
				exit(0);
			}
			default:{
				maze_print( x1, y2 );
				puts("wrong");
				break;
			}
		}
	}
	while( !( x1 == m && y2 == n ) );
	puts( "SUCCESS" );
	return 0;
}
