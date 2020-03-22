char *lock(char *string1){

    char *string2 = string1;

    for (;*string1;string1 ++){

        if(*string1==126){
            *string1 = 32;
            continue;
        }

        *string1 = *string1 + 1;
    }

    return string2;
}

char *unlock(char *string2){

    char *string1 = string2;

    for (;*string2;string2 ++){

        if(*string2==32){
            *string2 = 126;
            continue;
        }

        *string2 = *string2 - 1;
    }

    return string1;
}