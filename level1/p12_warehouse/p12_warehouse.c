#include <stdio.h>//写累了...
#include <windows.h>
#include <string.h>
#define open fopen("C:\\Users\\16585\\Desktop\\warehouse.txt","a+")//日常偷懒。
#define open1 fopen("C:\\Users\\16585\\Desktop\\warehouse.txt","r+")//只有在出库时才用这个,不然不能更改，a+为尾部.
//货物型变量
typedef struct warehouse
{
    char typename[20];//产品名称（相同产品，不同时间入库请在名字后方增加编号，不然取不出来别怪我,doge）
    int leftnum;//剩余数量
    int price;//单价
}cargo;
//菜单
void menu()//中文就是乱码...为了好看，只好用半桶水英文了
{
    system("CLS");
    printf("You can press 1~4 to realize the follow function!\n");
    printf("1:Show the cargos in your warehouse.\n");
    printf("2:Add new cargos to your warehouse.\n");
    printf("3:Take out the cargos from your warehouse.\n");
    printf("4:EXIT\n");
    char key=getch();
    switch(key)
    {
        case '1':show();break;
        case '2':takein();break;
        case '3':takeout();break;
        case '4':Exit();break;
        default:{printf("Please use 1~4!\a\nPlease typr enter!");getchar();menu();}break;
    }
}
//显示库存
void show()
{
    system("CLS");
    FILE *a;
    a=open;
    if(a==NULL)//地址错误，提升并自动退出。
    {
        printf("Fail to find the file,please change the location in line3 and restar!\n");
        Exit();
    }
    else//地址正确。
    {
        cargo b;//没错我没用指针！
        if((fscanf(a,"%s %d %d",b.typename,&b.leftnum,&b.price))==EOF)//仓库为空。
        {
            printf("Your warehouse is blank,you poor guy!\nYou can(only) press enter to continue.\n");
        }
        else//仓库不为空。
        {
            rewind(a);//文件指针回到初始位置。
            printf("typename\tleftnum\tprice\n");
            while((fscanf(a,"%s %d %d",b.typename,&b.leftnum,&b.price))!=EOF)
            {
                printf("%8s\t%7d\t%5d\n",b.typename,b.leftnum,b.price);
            }
            fclose(a);
            printf("This is all of your warehouse,you can(only) press enter to continue.\n");
        }
        getchar();
        menu();//只有文件位置正确才可以继续。
    }
}
//入库
void takein()
{
    system("CLS");
    FILE *a;
    a=open;
    if(a==NULL)//地址错误，提升并自动退出。
    {
        printf("Fail to find the file,please change the location in line3 and restar!\n");
        Exit();
    }
    else//地址正确。
    {
        cargo b;//没错我没用指针！
        printf("Please inpute the cargo'stypename and leftnum and price what youwant to add.\n");//本来想考虑相同货物合并的，不过既然考虑到价格和货源不同，不如就取不同名字就好了。
        int flag=0;
        while(flag==0)
        {
            scanf("%s %d %d",b.typename,&b.leftnum,&b.price);
            fprintf(a,"\n%20s%12d%12d",b.typename,b.leftnum,b.price);
            printf("continue add to press 1,else press 2\n");//判断是否继续加入。
            getchar();
            char c=getch();
            switch(c)
            {
                case '1':{printf("Please continue add\n");flag=0;}break;
                case '2':flag=1;break;
            }
        }
        fclose(a);
        printf("\nYou have finished adding,please press enter to continue\n");
        getchar();
        menu();//只有文件位置正确才可以继续。
    }
}
//出库
void takeout()
{
    system("CLS");
    FILE *a;
    a=open1;
    if(a==NULL)//地址错误，提升并自动退出。
    {
        printf("Fail to find the file,please change the location in line3 and restar!\n");
        Exit();
    }
    else//地址正确。
    {
        cargo b,c;//c为打算取出的货物，b为已有货物。
        printf("Please inpute the cargo'stypename and num what you want to take out.\n");
        scanf("%s%d",c.typename,&c.leftnum);
        getchar();
        int flag1=0;//判断是否找到货物
        while(fscanf(a,"%s %d %d",b.typename,&b.leftnum,&b.price)!=EOF)
        {
            if(strcmp(c.typename,b.typename)==0)
            {
                fseek(a, -24,SEEK_CUR);
                flag1=1;
                int flag2=0;//判断数量是否足够。
                while(flag2==0)
                {
                    flag2=(b.leftnum<c.leftnum)? 0:1;
                    if(b.leftnum<c.leftnum)
                    {
                        printf("ERROR!\nNow the leftnum of %s is only %d !\nplease intput a new num\n",b.typename,b.leftnum);
                        scanf("%d",&c.leftnum);
                        getchar();
                    }
                    else
                    {
                        int temp= b.leftnum - c.leftnum;
                        //fseek(a, 24, SEEK_CUR);
                        fprintf(a,"%12d%12d",temp,b.price);//规范输入的好处，直接更改（实际上是别的方法太复杂，不会，doge）
                        printf("You take out the %s,the leftnum is %d",b.typename,temp);
                    }
                }
                break;
            }
        }
        if(flag1==0)//货物不存在。
        {
            printf("The cargo:%s is not in your warehouse!\nYou can check your warehouse first.\n",c.typename);
        }
        fclose(a);
        printf("\nYou have finished ,please press enter to continue\n");
        getchar();
        menu();//只有文件位置正确才可以继续。
    }
}
//退出
void Exit()
{
    printf("Thanks for using my product,rember evaluate five star!!!\n");
    printf("You need to press enter to exit.");
    getchar();
}
int main()
{
    menu();//没有考虑用循环，每个函数后面都跟了一个menu函数。
    return 0;
}