#include"warehouse.h"
static void readMe();
int main(){ 
    loadList();
    readMe();

    unsigned temp;
    char mode,buf[MAXLEN+1];
    while(~scanf("%c",&mode)){ 
        mode=tolower(mode);
        switch(mode){ 
            case 's':
                showList();
                break;
            case 'i':
                scanf("%s %d",buf,&temp);
                insertItem(buf,temp);
                break;
            case 'd':
                scanf("%s %d",buf,&temp);
                deleteItem(buf,temp);
                break;
            case 'q':
            	dumpList();
                return 0;
            default:
                printf(">>>No such mode!\n");
        }
        getchar();
        //可恶的换行符会进入default
    }
    return 0;
}
inline void readMe() {
    printf("\n>>>>Read Me<<<<\n");
    printf("Usage:\n");
    printf("s : show the warehouse list\n");
    printf("q : dump the list and quit\n");
    printf("i X num : insert num Xs\n");
    printf("d X num : delete num Xs\n\n");
}