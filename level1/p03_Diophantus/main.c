#include <stdio.h>

int main()
{
    double age;
    double son;
    double start;
    for (age = 1; age <= 200; age++)
    {
        son = 0.5 * age;
        start = age * ( 1.0 / 6 + 1.0 / 12 + 1.0 / 7) + 5;
        if (age - 4 - start == son)
        {
            printf("%lf", age - 4);
            break;
        }
    }
}
