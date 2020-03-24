#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>
#define For(x,a,b) for(x=a;x<=b;x++)
int i,i1,i2;
struct cargo{//题目要求的两个货物信息
	char name[100];
	long int number;
};
int main(void)
{
	start:
	FILE *fp;
	struct cargo cargoes[865];//给一连串的货物留够空间，顺便致敬Qualcomm Snapdragon 865
	int choice,count,newnumber,flag;
	char next,container;
	char newname[100];
	count=0;
	printf("这是一个货物进销存的简单程序。请选择您想要执行的操作：\n");
	printf("0.退出    1.显示库存列表    2.入库    3.出库\n");
	scanf("%d",&choice);
	scanf("%c",&container);//这里的作用挺奇怪的，完全就是个替罪羊，因为输入数字以后的回车会直接被认为是货物名称输入完毕了，所以要找个东西承载这个回车
	if(choice==0){
		printf("感谢您的使用。\n");
		exit(0);
	} 
	if((fp=fopen("cargo.txt","r+"))==NULL){
		printf("打开库存文件错误。请重试。\n");
		exit(0);
	}
	while(1){//读入所有货物的信息 
		if((fscanf(fp,"%s  %d",&cargoes[count].name,&cargoes[count].number))==EOF) break;
		count++;
	}
	if(fclose(fp)){
		printf("关闭库存文件出现错误。程序即将退出。\n");//关闭文件，为的是一会可能以w的方式打开。 
		exit(0);
	}
	if(choice==1){
		printf("存货列表：\n");
		printf("货物名称          余量\n");//10个空格，输出好看一点吧。 
		for(i=0;i<count;i++){
			printf("%s",cargoes[i].name);
			For(i1,1,(18-strlen(cargoes[i].name))) printf(" ");//制表，使输出内容与表头对齐。
			printf("%d\n",cargoes[i].number);
		}
		printf("以上是仓库中所剩的所有货物。请视情况进货或出货。\n");
	}else if(choice==2){
		tryagain1:
		printf("请输入您想要入库的物品：\n");
		i2=0;
		while((newname[i2]=getchar())!='\n') i2++;//这样繁琐一些，但是可以读取空格 
		newname[i2]='\0';
		printf("请输入该商品的入库数量：\n");
		scanf("%d",&newnumber);
		scanf("%c",&container);//这里的作用挺奇怪的，完全就是个替罪羊，因为输入数字以后的回车会直接被认为是next输入完毕了，所以要找个东西承载这个回车
		flag=0;
		for(i=0;i<count;i++){
			if(strcmp(newname,cargoes[i].name)==0){//寻找之前有没有这种货物 
				flag=1;
				break;
			}
		}
		if(newnumber<=0){
			printf("入库失败！货物入库数量不能为零或负数！\n");
			Sleep(2000);
			goto tryagain1;
		} 
		if(flag==1){
			cargoes[i].number+=newnumber;//有这种货物，给这种货物加上入库的量 
			if((fp=fopen("cargo.txt","w"))==NULL){//重新打开文件 
				printf("打开库存文件错误。请重试。\n");
				exit(0);
			}
			if(fclose(fp)){
				printf("关闭库存文件出现错误。程序即将退出。\n");//以w方式打开已存在的文件然后再关闭，用以清除文件的全部内容 
				exit(0);
			}
			if((fp=fopen("cargo.txt","r+"))==NULL){
				printf("打开库存文件错误。请重试。\n");
				exit(0);
			}
			for(i1=0;i1<count;i1++){//全部重新写入 
				fprintf(fp,"%s  %d\n",cargoes[i1].name,cargoes[i1].number);
			}
		}else{
			if((fp=fopen("cargo.txt","r+"))==NULL){//重新打开文件 
				printf("打开库存文件错误。请重试。\n");
				exit(0);
			}
			fseek(fp,0,SEEK_END);
			fprintf(fp,"%s  %d\n",newname,newnumber);//没有这种货物，就加上这种货物。 
		}
	}else if(choice==3){
		tryagain2: 
		printf("请输入您想要出库的物品：\n");
		i2=0; 
		while((newname[i2]=getchar())!='\n') i2++;//这样繁琐一些，但是可以读取空格 
		newname[i2]='\0';
		printf("请输入该商品的出库数量：\n");
		scanf("%d",&newnumber);
		scanf("%c",&container);//这里的作用挺奇怪的，完全就是个替罪羊，因为输入数字以后的回车会直接被认为是next输入完毕了，所以要找个东西承载这个回车
		flag=0;
		for(i=0;i<count;i++){//之前一定有这种货物，找到它在哪 
			if(strcmp(newname,cargoes[i].name)==0){
				flag=1;
				break;
			}
		}
		if(newnumber<=0){
			printf("出货失败！出货数量不能为零或负数！\n");
			Sleep(2000);
			goto tryagain2;
		}
		if((cargoes[i].number-newnumber)<0&&flag!=0){
			printf("出货失败，库存中该种货物余量不足！请检查输入的出货数量并重试。\n");//得寸进尺 
			Sleep(2000);
			goto tryagain2;
		}
		if(flag==0){
			printf("出货失败，库存中没有这种货物！请检查输入的货物名称并重试。\n");//无中生有 
			Sleep(2000);
			goto tryagain2;
		}else{
			cargoes[i].number-=newnumber;//有这种货物，给这种货物减去出库的量 
			if((fp=fopen("cargo.txt","w"))==NULL){
				printf("打开库存文件错误。请重试。\n");
				exit(0);
			}
			if(fclose(fp)){
				printf("关闭库存文件出现错误。程序即将退出。\n");//以w方式打开已存在的文件然后再关闭，用以清除文件的全部内容 
				exit(0);
			}
			if((fp=fopen("cargo.txt","r+"))==NULL){//重新打开文件 
				printf("打开库存文件错误。请重试。\n");
				exit(0);
			}
			for(i1=0;i1<count;i1++){//库存非零的重新写入 
				if(cargoes[i1].number!=0){
					fprintf(fp,"%s  %d\n",cargoes[i1].name,cargoes[i1].number);
				}
			}
		}
	}else{
		printf("输入选项错误，请重试。\n");
		Sleep(2000);
		goto start;
	}
	if(choice!=1)//纯打开文件的时候没有二次打开文件，不需要再次关闭 
	if(fclose(fp)){
		printf("关闭库存文件出现错误。程序即将退出。\n");
		exit(0);
	}
	printf("想继续执行更多操作吗？\n请输入Y（是）或N（否）\n");
	scanf("%c",&next);
	if(next=='Y'){
		printf("大器已成，精进不止。\n");
		Sleep(2000);
		system("CLS");
		goto start;
	}else if(next=='N'){
		printf("突破所限，大有可能。\nNever Settle.\n");
	}
	system("pause");
	return 0;
}
