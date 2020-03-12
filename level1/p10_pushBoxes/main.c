#include <stdio.h>
#include "Game.h"
int main() {
    int Choice;
    while(1)
    {
        PrfMenu();
        scanf("%d", &Choice);
        FILE * map = MapChoice(Choice);
        if (map == NULL)
        {
            fflush(stdin);
            continue;
        }
        //¿ªÊ¼ÓÎÏ·
        Start(map, Choice);
        fclose(map);
    }
    return 0;
}
