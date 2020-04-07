#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
int maze[105][105];
int m, n, x, y, step;
int map_print( ){
	for( int i = 0; i < m; i++ ){
        for( int j = 0; j < n; j++ ){
			switch( maze[i][j] ){
				case 0: printf("  "); break;
				case 1: printf("¡ö"); break;
				case 3: printf("¡÷"); break;
				case 4: printf("¡ò"); break;
				case 5: printf("¡â"); break;
				case 7: printf("¡ñ"); break;
	            case 8: printf("¡â"); break;
	            default: break;
            }
        }
		puts("");
    }
    printf( "step:%d\n", step );
    return 0;
}
int man(){
	for( x = 0; x < m; x++ ){
		for( y = 0; y < n; y++ ){
			if( maze[x][y] == 5 || maze[x][y] == 8) break;
        }
		if (maze[x][y] == 5 || maze[x][y] == 8) break;
    }
    return 0;
}
int move(){
	step++;
	char c = getch();
	switch( c ){
    case 'W':
    case 'w':
        if( maze[x - 1][y] == 0 || maze[x - 1][y] == 3 ){
            maze[x - 1][y] += 5;                
            maze[x][y]  -= 5;
        }
        if( ( maze[x - 1][y] == 4 || maze[x - 1][y] == 7) && 
            ( maze[x - 2][y] == 0 || maze[x - 2][y] == 3) ) {
            maze[x - 2][y] += 4;
            maze[x - 1][y] += 1;
            maze[x][y] -= 5;
        }
        break;
    case 'A':
    case 'a':
        if( maze[x][y-1] == 0 || maze[x][y-1] == 3 ){
            maze[x][y-1] += 5;
            maze[x][y] -= 5;
        }
        if ( ( maze[x][y-1] == 4 || maze[x][y-1] == 7 ) &&
            ( maze[x][y-2] == 0 || maze[x][y-2] == 3 ) ){
            maze[x][y - 2] += 4;
            maze[x][y - 1] += 1;
            maze[x][y] -= 5;
        }
        break;
    case 'S':
    case 's':
        if(maze[x + 1][y] == 0 || maze[x + 1][y] == 3 ){
            maze[x + 1][y] += 5;
            maze[x][y] -= 5;
        }
		if( (maze[x + 1][y] == 4 || maze[x + 1][y] == 7 ) &&
			(maze[x + 2][y] == 0 || maze[x + 2][y] == 3 ) ){
            maze[x + 2][y] += 4;
            maze[x + 1][y] += 1;
            maze[x][y] -= 5;
        }
        break;
    case 'D':
    case 'd':
		if( maze[x][y + 1] == 0 || maze[x][y + 1] == 3 ){
            maze[x][y + 1] += 5;
            maze[x][y] -= 5;
        }
        if( ( maze[x][y + 1] == 4 || maze[x][y + 1] == 7 ) &&
            ( maze[x][y + 2] == 0 || maze[x][y + 2] == 3) ){
            maze[x][y + 2] += 4;
            maze[x][y + 1] += 1;
            maze[x][y] -=5;
        }
        break;
    }
    return 0;
}
int main(){
	FILE *mf; 
	if( ( mf = fopen( "Bo.txt", "r" ) ) == NULL ){
		puts("ERROR");
		exit(0);
	}
	fscanf( mf, "%d %d\n", &m, &n );
	while( !feof( mf ) ){
		for( int i = 0; i < m; i ++ ){
			for( int j = 0; j < n; j ++ ){
				fscanf( mf, "%d ", &maze[i][j] );
			}
		}
	}
	while (1){
		map_print();
		man();
		move();
		bool fal = 0;
		for( int i = 0; i < m; i ++ )
			for( int j = 0; j < n; j++ )
				if( maze[i][j] == 4 ){
					fal = 1; break;
				} 
		if( !fal ) break;
		system("cls");
	}
	printf( "congratulations!\n" );
	printf( "step:%d\n", step );
	system("pause");
	return 0;
}
