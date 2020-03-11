#include <stdio.h>

int main() {
    float D_Life = 0;
    float ChildrenTime;
    float TeenagerTime;
    float SingleTime;
    float AfterMarriageTime = 5;
    float D_Son_Life;
    float AfterSonDead = 4;
    while (1)
    {
        ChildrenTime = D_Life/6;
        TeenagerTime = D_Life/12;
        SingleTime = D_Life/7;
        D_Son_Life = D_Life/2;
        if(ChildrenTime+TeenagerTime+SingleTime+D_Son_Life+AfterMarriageTime+AfterSonDead == D_Life)
            break;
        D_Life++;
    }
    printf("%d", (int)D_Life-4);
    return 0;
}
