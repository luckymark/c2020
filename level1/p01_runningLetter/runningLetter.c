#include<stdio.h>
#include<windows.h>
#include <stdlib.h>
int main()
{
    const int TIME=250;
    int n,k;
    char letter;
    scanf("%s",&letter);
    for(n=1;n<=25;n++){
    	  system("cls");
    	for(k=0;k<=n;k++){
    		printf(" ");
		}
    	
    	
      
            printf("%c",letter);
            sleep(TIME);
           
           
        
        
       }
       
        for(n=25;n>=0;n--){
        	    system("cls");
    	for(k=0;k<n;k++){
    		printf(" ");
		}
    	
    	
      
            printf("%c",letter);
            sleep(TIME);
         
           
        
        
       }
        
        return 0;


}

