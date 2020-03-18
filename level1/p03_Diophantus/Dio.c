#include <stdio.h>

int main()
{
    int i,dio;
    for (i=1;;i++){
        dio = 7*i; //dio的年龄是7的倍数
        if( !(dio%12) && dio/2 == dio-dio/6-dio/12-dio/7-5-4){ //dio的年龄是十二的倍数
            printf("儿子死的时候丢番图%d岁\n",dio-4);
            break;}
        }

}

