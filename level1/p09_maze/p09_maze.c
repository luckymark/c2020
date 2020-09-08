#include<stdio.h>
#include<stdlib.h>
int main()
{
    char a[10][10]={{'#', '#','#','#','#','#','#','#','#','#' } ,
                    {'#', ' ','$','#','#','#','#','#','#','#' } ,
                    {'#', ' ','#',' ',' ','#','#','#',' ',' ' } ,
                    {'#', ' ','#',' ',' ','#',' ',' ',' ','#' } ,
                    {'#', ' ','#','#',' ','#',' ','#','#','#' } ,
                    {'#', ' ','#','#',' ','#',' ','#','#','#' } ,
                    {'#', ' ','#',' ',' ',' ',' ','#','#','#' } ,
                    {'#', ' ','#',' ','#','#',' ','#','#','#' } ,
                    {'#', ' ',' ',' ','#',' ',' ',' ',' ','#' } , 
                    {'#', '#','#','#','#','#','#','#','#','#' } };
    char mx=1,my=2,exitx=2,exity=9;
    while(1)
    { 
        system("CLS");
        printf("PLEASE PRESS DIRECTION KEY TO MOVE'$'TO EXIT\n");
        for(int i=0;i<10;i++)
        {
  	        for(int j=0;j<10;j++)
            {
		        printf("%c",a[i][j]);
  	        }	
            printf("\n");
        }
    if(mx==exitx&&my==exity)
    {
        printf("YOU HAVE WIN!,PLEASE PRESS Enter"); 
        getchar();
  	    break;
    }
    int order=getch();
    a[mx][my]=' ';
    switch(order)
    {
        case 72: if(' '==a[mx-1][my]) mx--;break;	//上
        case 80: if(' '==a[mx+1][my]) mx++;break;	//下
        case 77: if(' '==a[mx][my+1]) my++;break;	//右
        case 75: if(' '==a[mx][my-1]) my--;break;	//左
    }
    a[mx][my]='$';
 }
   
}