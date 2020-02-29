#include <stdio.h>

const int MAX = 130;

int fatherAge(){
    int age ;
    for(age=20;age<MAX;age++){
        if(age%12!=0) continue;
        else if(age%7!=0) continue;
        else if(age/6+age/12+age/7+5+age/2+4==age) return age;
    }
    return -1;
}


int main(){
    int Age = fatherAge();
    int nowAge = Age-4;
    printf("%d",nowAge);

    return 0;
}