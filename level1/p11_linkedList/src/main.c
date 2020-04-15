#include"linkedList.h"
int main(){
    makeList();

    printf("\nIn order:\n");
    showList();

    printf("\n\nFind 5 firstly:\n");
    printf("%d",findNext(5,DEFAULT));

    printf("\nFind 5 secondly:\n");
    printf("%d\n",findNext(5,DEFAULT));

    reverseList(head,NULL);
    printf("\nReversed:\n");
    showList();

    return 0;
}
