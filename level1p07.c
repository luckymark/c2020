#include<stdio.h>
#include<string.h>
#define maxn 1010
struct Str
{
	char str[maxn];
	int len;
};
struct Str encrypt(struct Str s)
{
	struct Str ret={{""},s.len};
	for(int i=1;i<=s.len;i++)
		ret.str[i]=s.str[i]+1;
	return ret;
}
struct Str decrypt(struct Str s)
{
	struct Str ret={{""},s.len};
	for(int i=1;i<=s.len;i++)
		ret.str[i]=s.str[i]-1;
	return ret;
}
int main()
{
	struct Str flie={{""},0}; 
	scanf("%s",flie.str+1);
	flie.len=strlen(flie.str+1);
	struct Str ciphertext=encrypt(flie);
	struct Str newflie=decrypt(ciphertext);
	printf("flie after encrypt:%s\n",ciphertext.str+1);
	printf("ciphertext after decrypt:%s\n",newflie.str+1);
	return 0;
}
