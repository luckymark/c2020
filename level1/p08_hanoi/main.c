#include <stdio.h>
void move (int n, char a, char c){
    printf("move %d from %c to %c\n", n, a, c);
}
void Hanoi (int n, char a, char c, char b)
{
    if (n == 1)
    {
        move(n, a, c);
        return;
    }
    Hanoi(n-1, a, b, c);
    move(n, a, c);
    Hanoi(n-1, b, c, a);
    return;
}
int main() {
    int n = 64;
    char a = '1';
    char b = '2';
    char c = '3';
    Hanoi(n, a, b, c);
    return 0;
}
