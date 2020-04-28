# include  <stdio.h>

void hanoi ( int n, char a,  char b,  char c );

int main ()
{  	
	int  n ;
	printf( "请输入你的原始层数:") ;
	scanf("%d",&n) ;
	printf( "移动步骤为:\n") ;
	hanoi ( n,  'A' ,  'B' , 'C' ) ;
   	return 0;
   }

void hanoi ( int n, char a,  char b,  char c ) {
	if  (1 == n){
			printf("%c-->%c\t",a,c);
	}else{
		hanoi ( n-1,  a,  c,  b ) ;                  
     	printf("%c-->%c\t",a , c) ;               
     	hanoi ( n-1,  b,  a,  c ) ;         
	}            
}
