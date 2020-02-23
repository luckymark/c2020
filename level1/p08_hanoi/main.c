#include <stdio.h>
void hanoi(int n, char from, char mid, char to);

int moves = 0;

int main(void) {
    int n;

    printf("Please enter the quantity of disks: ");
    scanf("%d", &n);
    hanoi(n, 'A', 'B', 'C');
    printf("Totally move %d times.\n", moves);

    return 0;
}

void hanoi(int n, char from, char mid, char to) {
    if (n == 0)
        return;
    hanoi(n-1, from, to, mid);
    printf("Move disk %d from %c to %c\n", n, from, to);
    moves++;
    hanoi(n-1, mid, from, to);
}
