#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h> //按键检测
#define MAX 10000

struct Cargo{
    char modelNumber[40];//型号
    double stock;//库存
    double price;//进价
    char name[40];//商品名
    char merchant[40];//商家
}cargo[MAX]={{"\0",0.0,0.0,"0","0"}};
int num;

void menu();//菜单
void print(int num);//显示库存
int input(int num);//入库
void output(int num);//出库

int main(){
    FILE *fp;
    fp=fopen("C://Users//ZYW//temp//warehouse.txt","a+");
    for(num=0;;num++){
        if(fscanf(fp,"%s%lf%lf%s%s",cargo[num].modelNumber,&cargo[num].stock,&cargo[num].price,cargo[num].name,cargo[num].merchant)!=EOF){
        }else break;
    }
    while(1){
        menu();
        char key=getch();
        switch(key){
            case '1':
                print(num);
                break;
            case '2':
                num=input(num);
                break;
            case '3':
                output(num);
                break;
            case '4':
                break;
            default:
                printf("\a");
                break;
        }if(key=='4'){
            break;
        }
    }
    fp=fopen("C://Users//ZYW//temp//warehouse.txt","w+");
    fprintf(fp,"库存列表\n型号\t数量\t进价\t商品名\t商家\n");
    for(int i=0;i<num;i++){
        fprintf(fp,"%s\t%.2f\t%.2f\t%s\t%s\n",cargo[i].modelNumber,cargo[i].stock,cargo[i].price,cargo[i].name,cargo[i].merchant);
    }fclose(fp);
    return 0;
}

void menu(){
    system("cls");
    printf("你可以选择以下操作:(按数字选择相应功能)\n");
    printf("1-显示库存列表\n");
    printf("2-入库\n");
    printf("3-出库\n");
    printf("4-退出程序\n");
}
void print(int num){
    system("cls");
    printf("存货列表\n型号\t数量\t进价\t商品名\t商家\n");
    for(int i=0;i<num;i++){
        printf("%s\t%.2f\t%.2f\t%s\t%s\n",cargo[i].modelNumber,cargo[i].stock,cargo[i].price,cargo[i].name,cargo[i].merchant);
    }printf("\n\n");
    system("pause");
}
int input(int num){//入库
    system("cls");
    printf("入库\n按f输入，按j结束\n");
    printf("按顺序输入:型号，入库数量，进价，商品名，商家\n");
    char ch;
    char tempModel[40];
    while(1){
        ch=getch();
        if(ch=='j'){
            return num;
        }else if(ch=='f'){
            int flag=0;
            scanf("%s",tempModel);
            for(int i=0;i<num;i++){
                if(!strcmp(tempModel,cargo[i].modelNumber)){
                    double add;
                    scanf("%lf%lf%s%s",&add,&cargo[i].price,cargo[i].name,cargo[i].merchant);
                    cargo[i].stock+=add;
                    flag=1;            
                }
            }if(!flag){
                strcpy(cargo[num].modelNumber,tempModel);
                scanf("%lf%lf%s%s",&cargo[num].stock,&cargo[num].price,cargo[num].name,cargo[num].merchant);
                num++;
            }
        }else{
            printf("\a");
        }
    }
}
void output(int num){
    system("cls");
    printf("出库\n按f输入，按j结束\n");
    printf("按顺序输入:型号，出库数量\n");
    char ch;
    while(1){
        ch=getch();
        if(ch=='j'){
            return;
        }else if(ch=='f'){
            char temp[40];
            double sub;
            int i=0;
            scanf("%s",temp);
            for(;i<num;i++){
                if(!strcmp(cargo[i].modelNumber,temp)){
                    scanf("%lf",&sub);
                    cargo[i].stock-=sub;
                    printf("完成\n");
                    break;
                }
            }if(i==num){
                printf("无库存，请检查是否输入错误\n");
            }
        }else {
            printf("\a");
        }
    }
}

