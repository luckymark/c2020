#include<windows.h>
#include<string.h>
#include<stdio.h>
typedef struct cargo{
	char *name; int num;
}cargo;
typedef struct Node{
	cargo goods;
	struct Node *pre, *next;
}Node;
Node *head, *tail;
void NewNode(){
	Node* fa = tail;
	if( tail == NULL ) head = tail = ( Node * ) malloc( sizeof( Node ) );
	else{ ( * tail ).next = ( Node * ) malloc( sizeof( Node ) ); tail = ( * tail ).next; }
	if( fa != NULL ) ( * fa ).next = tail;
	( * tail ).pre = fa;
	( * tail ).next = NULL;
}
int main(){
	puts("++++++++++++++++++++++");
	puts("1.存货列表");
	puts("2.入库");
	puts("3.出库");
	puts("4.退出程序");
	puts("++++++++++++++++++++++");
	char Name[105]; int Num, len, opt;
	FILE * file_ = fopen( "box.txt", "r" );
	while( fscanf( file_, "%s%d", Name, &Num ) != EOF ){
		NewNode( );
		len = strlen( Name );
		( * tail ).goods.name = ( char * ) malloc(sizeof(char)*( len + 1 ));
		strcpy( ( * tail ).goods.name, Name );
		( * tail ).goods.num = Num;
	}
	fclose( file_ );
	while(1){
		scanf( "%d", &opt );
		if( opt == 1 )
			for( Node* p = head; p != NULL; p = ( * p ).next ){
				printf( "%s %d\n", ( * p ).goods.name, ( * p ).goods.num );
			}
		if( opt == 2 ){
			scanf( "%s%d", Name, &Num );
			int flag = 0;
			for( Node* p = head; p != NULL; p = ( * p ).next ){
				if( strcmp( ( * p ).goods.name, Name ) == 0 ){
					( * p ).goods.num += Num ;
					flag = 1; break;
				}
			}
			if( !flag ){
				NewNode( );
				len = strlen( Name );
				( * tail ).goods.name = ( char * )malloc(sizeof(char) * ( len + 1 ));
				strcpy( ( * tail ).goods.name, Name );
				( * tail ).goods.num = Num;
			}
		}
		if( opt == 3 ){
			scanf( "%s%d", Name , &Num );
			for( Node* p = head; p !=  NULL; p = ( * p ).next ){
				if( strcmp( ( * p ).goods.name, Name ) == 0 ){//  s1==s2->0 s1>s2-> >0 
					( * p ).goods.num -= Num;
					if( ! ( * p ).goods.num ){
						if( ( * p ).pre != NULL ) ( * ( ( * p ).pre ) ).next = ( * p ).next;
						if( ( * p ).next != NULL ) ( * ( ( * p ).next ) ).pre = ( * p ).pre;
						if( p == head ) head = ( * p ).next;
						if( p == tail ) tail = ( * p ).pre;
						free(p);
					}
					break;
				}
			}
		}
		if( opt == 4 ){
			break;
		}
	}
	file_ = fopen("WAREHOUSE.txt","w");
	for( Node* p = head; p != NULL; p = (*p).next ) fprintf( file_, "%s %d\n", (*p).goods.name, (*p).goods.num );
	fclose( file_ );
	return 0;
}
