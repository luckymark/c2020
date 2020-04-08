#include "aboutmap.h"

elemtype Switch(char**map,char c,int x,int y){
    switch (c) {
        case 'W' :
            if (x < 1 || '#' == *((char *) map + col * (x - 1) + y))
            {
                return x;
                break;
            }
            else {
                *((char *) map + col * (x - 1) + y)='a'+*((char *) map + col * (x - 1) + y)-' ';
                *((char *) map + col * x + y)=*((char *) map + col * x + y)-'a';
                return x-1;
                break;
//                swap(map,x,y,x-1,y);
            }
        case 'A' :
            if (y < 1 || '#' == *((char *) map + col * x + y-1))
            {
                return y;
                break;
            }
            else{
                *((char *) map + col * x + y-1)='a'+*((char *) map + col * x + y-1)-' ';
                *((char *) map + col * x + y)=*((char *) map + col * x + y)-'a';
                return y-1;
                break;
//                swap(map,x,y,x,y-1);
            }
        case 'S' :
            if (y > 3 || '#' == *((char *) map + col * (x + 1) + y))
            {
                return x;
                break;
            }
            else{
                *((char *) map + col * (x + 1) + y)='a'+*((char *) map + col * (x + 1) + y)-' ';
                *((char *) map + col * x + y)=*((char *) map + col * x + y)-'a';
                return x+1;
                break;
            }
        case 'D':
            if (x > 3 || '#' == *((char *) map + col * x + y+1))
            {
                return y;
                break;
            }
            else{
                *((char *) map + col * x + y+1)='a'+*((char *) map + col * x + y+1)-' ';
                *((char *) map + col * x + y)=*((char *) map + col * x + y)-'a';
                return y+1;
                break;
            }
        default: return x;
    }
//    printf("%c",*((char*)go + col*x + y));
}