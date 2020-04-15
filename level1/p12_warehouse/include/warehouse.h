#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAXLEN 10
#define FILENAME "ware.txt"

struct item{ 
    char name[MAXLEN+1];
    unsigned number;
    struct item* next;
};
extern struct item* head;

bool loadList();
bool dumpList();
void showList();
struct item* findItem(char name[]);
bool insertItem(char name[],unsigned number);
bool deleteItem(char name[],unsigned number);
static FILE* fOpen(char * filename,char * mode);

inline FILE* fOpen(char * filename,char * mode){ 
    FILE *temp=fopen(filename,mode);
    if(temp)return temp;
    else{ 
        printf("\nFileOpen Error! %s : %s : %d\n",__FILE__,__func__,__LINE__);
        return NULL;
    }
}
