#include <stdio.h>
#include <stdlib.h>
int push (int * Stack, int ** Stack_ptr, int n)
{
    **Stack_ptr = n;
    if (*Stack_ptr != &Stack[0])
        (*Stack_ptr)--;
}
int pop (int *Stack, int **Stack_ptr)
{
    int temp = **Stack_ptr;
    if (*Stack_ptr != &Stack[19])
        (*Stack_ptr)++;
    return temp;
}
int main() {
    int i;
    int An_Num;
    int Stack[20];
    int * Stack_ptr = &Stack[19];
    //char * Op_ptr = NULL;
    char Op_string[21];
    scanf("%s", Op_string);
    for (i = (sizeof(Op_string)/ sizeof(Op_string[0]) - 1); i >= 0;i--)
    {
        if (Op_string[i] <= '9' && Op_string[i] >= '0')
        {
            push(Stack, &Stack_ptr, Op_string[i] - '0');
            continue;
        }
        switch (Op_string[i])
        {
            case '+':
                if (&Stack_ptr == &Stack[19])
                {
                    printf("error");
                    break;
                }
                An_Num = pop(Stack,&Stack_ptr) + pop(Stack,&Stack_ptr);
                push(Stack, &Stack_ptr, An_Num);
                break;
            case '-':
                if (&Stack_ptr == &Stack[19])
                {
                    printf("error");
                    break;
                }
                An_Num = pop(Stack,&Stack_ptr) - pop(Stack,&Stack_ptr);
                push(Stack, &Stack_ptr, An_Num);
                break;
            case 'x':
                if (&Stack_ptr == &Stack[19])
                {
                    printf("error");
                    break;
                }
                An_Num = pop(Stack,&Stack_ptr) * pop(Stack,&Stack_ptr);
                push(Stack, &Stack_ptr, An_Num);
                break;
            case '/':
                if (&Stack_ptr == &Stack[19])
                {
                    printf("error");
                    break;
                }
                An_Num = pop(Stack,&Stack_ptr) / pop(Stack,&Stack_ptr);
                push(Stack, &Stack_ptr, An_Num);
                break;
        }
        printf("%d", An_Num);
    }
    return 0;
}
