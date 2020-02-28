//#include <stdio.h>
#include "list_base.h"


int main()
{
    // build & init a list
    _list list1;
    init_list(&list1);

    // the first input and get all the values in the list
    input_list(&list1);
    output_list(list1);

    // the second input and get all the values in the list
    input_list(&list1);
    output_list(list1);

    // reverse the list and get all the values in the list
    reverse_list(&list1);
    output_list(list1);

    // find the value(5) and printf all the numbers which the value is in the list
    find_all(&list1,FIND_VALUE);

    // delete the list
    del_list(&list1);

    // end the program
    return 0;
}
