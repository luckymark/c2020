#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define For(x,a,b) for(x=a;x<=b;x++)
void encrypt(char content[]);
void decrypt(char content[]); 
long long int i,i1,i2;
int main(void)
{
	char content[10980];                                                          //设置足够字符范围，顺便致敬Intel Core i9-10980XE
	int setting;
	char container;
	i=0;
	printf("这是一个对输入的内容根据Base64规则进行加密或解密的程序。\n");
	printf("请输入操作选项：\n");
	printf("1. 加密      2. 解密      0. 退出\n");
	scanf("%d",&setting);
	if(setting==0) exit(0);
	else if(setting!=0&&setting!=1&&setting!=2){
		printf("输入选项错误。请稍后重试。\n");
		exit(0);
	}
	scanf("%c",&container);                         //这里的作用挺奇怪的，完全就是个替罪羊，因为输入数字以后的回车会直接被认为是content输入完毕了，所以要找个东西承载这个回车 
	printf("请输入待处理的内容,以回车符结束输入：\n");
	while((content[i]=getchar())!='\n') i++;
	content[i]='\0';
	if(setting==1) encrypt(content);
	else if(setting==2) decrypt(content);
	system("pause");
	return 0;
}
void encrypt(char content[])                                     //加密部分 
{
	long long int oldlen,newlen,j;                                 //oldlen是明码的长度，newlen是密码的长度 
	char base64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";     //Base64编码规则表，类似于ASCII码表
	char *encode;
	j=0;
	oldlen=strlen(content);
	if(oldlen%3==0) newlen=oldlen/3*4;
	else newlen=(oldlen/3+1)*4;
	if((encode=(char *)malloc((newlen*sizeof(char)+1)))==NULL){       //动态分配空间，并且设置分配出错检测。这里一定要加一！加一啊啊喂！要不'\0'可能没地方放了！ 
		printf("分配内存失败。程序异常退出。");//此处使用calloc也可以，但是也得在sizeof(char)后面加1，以容纳'\0'。 
		exit(1);//newlen*sizeof(char)+1和newlen*(sizeof(char)+1)是一样的，因为sizeof(char)=1，即char只占一个字节（8个二进制位），int啥的就不一样了！ 
	}
	//每3个8位二进制数化为4个6位数，如aaaaaa\aabbbb\bbbbcc\cccccc，然后按照Base64加密法按照十进制对应生成形成6个字符 
	for(i1=0,i2=0;i1<newlen-2;i1+=4,i2+=3){                     //为什么使用i1<newlen-2，而不是i1<newlen ? 解释分析见程序末尾1。 
		encode[i1]=base64[content[i2]>>2];
		encode[i1+1]=base64[(content[i2]&0x3)<<4 | (content[i2+1]>>4)];
		encode[i1+2]=base64[(content[i2+1]&0xf)<<2 | (content[i2+2]>>6)];
		encode[i1+3]=base64[(content[i2+2])&0x3f];
	}
	switch(oldlen%3){
		case 1: encode[i1-2]=encode[i-1]='=';  break;          //Base64密码的位数一定是4的倍数，不够4位要在末尾用等于号补齐 
		case 2: encode[i1-1]='=';  break;                      //为什么不会加3个等于号？见2 
	}
	encode[newlen]='\0';
	printf("这是加密后的字符：\n");
	while(encode[j]!='\0'){
		printf("%c",encode[j]);
		j++;
	}
	printf("\n");
	free(encode);
}
void decrypt(char content[])										//解密部分 
{
    int base[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,	//将Base64编码与ASCII编码一一对应，如base[]中的“51”元素是base[122]，代表Base64中的51号元素，ASCII中的122号元素“z” 
				0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,62,0,0,0,		//前面的一堆0是因为ASCII码里面的这些字符没有对应的Base64代码，无法被解密 
				63,52,53,54,55,56,57,58,59,60,61,0,0,0,0,0,0,0,0,
				1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,
				22,23,24,25,0,0,0,0,0,0,26,27,28,29,30,31,32,33,34,35,
				36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51
    };
    long long int oldlen,newlen,j;                              //oldlen是密码的长度，newlen是明码的长度 
    char *decode;
    j=0;
    oldlen=strlen(content);
    if(strstr(content,"==")) newlen=oldlen/4*3-2; 
	else if(strstr(content,"=")) newlen=oldlen/4*3-1;
	else newlen=oldlen/4*3;
	if((decode=(char*)calloc(newlen+1,sizeof(char)))==NULL){       //动态分配空间，并且设置分配出错检测
		printf("分配内存失败。程序异常退出。");
		exit(1);
	}
	for(i1=0,i2=0;i2<oldlen-2;i1+=3,i2+=4){
		decode[i1]=((char)base[content[i2]]<<2)|((char)base[content[i2+1]]>>4);
		decode[i1+1]=((char)base[(content[i2+1])]<<4)|((char)base[content[i2+2]]>>2);//这里不需要&0x0f，原因见3 
		decode[i1+2]=((char)base[(content[i2+2])]<<6)|(char)base[content[i2+3]];
	}
	decode[newlen]='\0';
	printf("这是解密后的字符：\n");
	while(decode[j]!='\0'){
		printf("%c",decode[j]);
		j++;
	}
	printf("\n");
	free(decode);
}
//1. 47行 为什么使用i1<newlen-2，而不是i1<newlen ?
// 首先我们必须明白Base64的编码规则。Base64是将3个字符的ASCII码转换为8位二进制数字，然后合并三个二进制数再每六个数字为一组进行截断，如aaaaaa\aabbbb\bbbbcc\cccccc，然后
// 将这四个二进制数字再转回十进制数字，依靠Base64编码表通过数字一一找出对应的字符。也就是当明码的位数是3的倍数时，位数会整整增加1/3的长度。
// 但是如果明码的位数不是3的倍数呢？
// 位数为3n+1时,最后一个数字按照规则会截取得到两个数字,两个数的二进制数分别有6位和2位。则后面的两位数字会在后面补四个0得到一个六位字符,然后再分别得到两个Base64字符。
// 还有一点,Base64加密后位数必须是4的倍数,不够四位要在后面补"="号。那么此时,就要在后面补两个"="号。 
// 比如单字符"M",其ASCII码为77,二进制数为01001101,截取得010011和01,然后补全得010011和010000,二者分别对应19和16,于是得到Base64密码TQ==。 
// 位数为3n+2时亦然,但是会得到三个字符的Base64密码,然后加"="变为四位。如明码"DL",加密后会得到"REw="。
// 现在来回答上面的那个问题。可以看出,按程序中那样每三位一划分,可能出现最后一组只剩一个字符的情况,然后转换为Base64密码后未加等号前成为两个字符。或者最后一张只剩两个字符,
// 转换后成为三个字符。也就是最少可能只有两个Base64字符。如果使用i1<newlen会怎么样呢?最后一轮处循环可能会判断为该循环没有走完——因为最后一组只有两个Base64字符,确实小于
// newlen的四个。然后循环会再来一轮...这不是很奇怪吗?没有分配那么多内存,要是再走一轮,谁知道会出现什么奇怪的错误QAQ。
//2. 55行 为什么不会加3个等于号？
// 上面讲了,未加等号前最后一组最少有两个字符。嗯,要凑齐四位,也就最多只需要两个"="啦。这也是用i1-2,i1-1的原因,因为后几位还没用完啊,再加就爆内存了。
//3. 88和89行 为什么不需要&0x之类的？
// 因为char只有8个二进制位，左移4位后会舍弃前4位，而不会出现12位的二进制数。也就是说，这里的<<兼具移位和取后几位的作用，无需多此一举再专门取位。 
//4. 题外话,为什么你要写这么奇怪的东西?看这个题的要求,难道不是只需要一个什么str[i] += i;或者str[i] -= i;之类的就完了吗?何必自讨苦吃,费力不讨好? 
// 其实很简单哈,本人博客(MinatoXeon.github.io)上面有一大堆被转成Base64的手机机型代码(感兴趣的话欢迎去捧场),自己写一个Base64加密解密的程序毕竟方便而且没有后顾之忧嘛。顺便
// 利用这个机会学一下Base64编码规则和4*6转3*8类似的转换技巧,这无疑是一举两得啊。
// NEVER SETTLE. 
