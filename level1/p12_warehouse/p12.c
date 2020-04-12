/*垃圾代码...哎...*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct goods {
    char type;
    int number;
};

static int hasType(struct goods store[],int type_number,char type){
    for(int i=0;i<type_number;i ++){
        if(store[i].type==type){
            return 1;
        }
    }
    return 0;
}

static void showGoods(struct goods store[],int* type_number){
    printf("Type:\t");
    for (int i = 0; i < *type_number; i++) {
        printf("%c\t",store[i].type);
    }
    printf("\n");

    printf("Number:\t");
    for (int i = 0; i < *type_number; i++) {
        printf("%d\t",store[i].number);
    }
    printf("\n");
}
static void goods_in(struct goods store[],int* type_number){
    char in_type;
    int in_number;

    printf("请输入入库的货物型号:\n");
    scanf(" %c",&in_type);
    printf("请输入入库的货物数量:\n");
    scanf(" %d",&in_number);

    if(in_number<=0){
        printf("无效入库数量！\n");
        return;
    }

    if(hasType(store,*type_number,in_type)){
        for(int i=0;i<*type_number;i ++){
            if(store[i].type==in_type){
                store[i].number +=in_number;
            }
        }
    }else{
        store[*type_number].type=in_type;
        store[*type_number].number=in_number;
        *type_number =*type_number+1;
    }
}

static void goods_out(struct goods store[],int* type_number){
    char out_type;
    int out_number;

    printf("请输入出库的货物型号:\n");
    scanf(" %c",&out_type);
    printf("请输入出库的货物数量:\n");
    scanf(" %d",&out_number);

    if(out_number<=0){
        printf("无效出库数量！\n");
        return;
    }

    if(hasType(store,*type_number,out_type)){
        for(int i=0;i<*type_number;i ++){
            if(store[i].type==out_type){
                if(store[i].number>=out_number){
                    store[i].number=store[i].number-out_number;
                }else{
                    printf("此类型货物数量不足！\n");
                }
            }
        }
    }else{
        printf("暂无此类型货物！\n");
    }
}

static void systemExit(struct goods store[],int* type_number){
    FILE* fpw=fopen("storeData.txt","w+");
    char temp[7];
    int temp_count=7;
    for(int i=0;i<*type_number;i++){

        for(int k=0;k<temp_count;k++){
            temp[k]='\0';
        }
        temp_count=0;
        strcpy(temp,&store[i].type);
        while(temp[temp_count]!='\0'){
            fwrite((const void *)&temp[temp_count], 1, 1, fpw);
            temp_count++;
        }
        fwrite(" ",1,1,fpw);

        for(int k=0;k<temp_count;k++){
            temp[k]='\0';
        }
        temp_count=0;
        itoa(store[i].number,temp,10);
        while(temp[temp_count]!='\0'){
            fwrite((const void *)&temp[temp_count], 1, 1, fpw);
            temp_count++;
        }
        fwrite(" ",1,1,fpw);
    }
    fclose(fpw);
    exit(0);
}

static void menu(struct goods store[],int* type_number){
    int choice;
    printf("选择功能对应数字输入：\n1:显示存货列表\n2:入库\n3:出库\n4:退出程序\n");
    scanf(" %d",&choice);
    switch (choice){
        case 1:
            showGoods(store,type_number);
            break;
        case 2:
            goods_in(store,type_number);
            break;
        case 3:
            goods_out(store,type_number);
            break;
        case 4:
            systemExit(store,type_number);
            printf("Finished!\n");
        default:
            printf("非法输入！请重新输入！\n");
    }
}

static void goods_create(struct goods* goods_p,char type,int number){
    goods_p->type=type;
    goods_p->number=number;
}

static char* toString(char temp[],int temp_count){
    char* sp;
    for(int i=0;i<temp_count;i++){
        sp[i]=temp[i];
    }
    return sp;
}

int main(){

    FILE* fpr=fopen("storeData.txt","r");
    char stream,data[1024];
    int count=0;
    stream=fgetc(fpr);
    while(stream!=EOF){
        data[count]=stream;
        count ++;
        stream=fgetc(fpr);
    }
    fclose(fpr);

    char temp[7];
    int data_count=0;
    int temp_count=7;
    struct goods store[25];
    int store_count=0;

    while(data_count<count){
        for(int i=0;i<temp_count;i++){
            temp[i]='\0';
        }
        temp_count=0;
        while (data[data_count]!=' '){
            temp[temp_count]=data[data_count];
            temp_count++;
            data_count++;
        }
        char* type_p=toString(temp,temp_count);
        char type= *type_p;
        data_count++;
        for(int i=0;i<temp_count;i++){
            temp[i]='\0';
        }
        temp_count=0;
        while (data[data_count]!=' '){
            temp[temp_count]=data[data_count];
            temp_count++;
            data_count++;
        }
        int number=atoi(temp);
        data_count++;
        goods_create(&store[store_count],type,number);
        store_count++;
    }
    int type_number=store_count;

    for(;;){
        menu(store,&type_number);
    }
}