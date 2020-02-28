#include <stdio.h>

int main(){
    for (int age = 42; age < 150; ++age) {
        if (!(age % 12 == 0 && age % 7 == 0)){
            continue;
        }
        int sonDie = age / 6 + age / 12 + age / 7 + 5 + age / 2;
        if (age - sonDie == 4){
            printf("%d",sonDie);
        }
    }
    return 0;
}
