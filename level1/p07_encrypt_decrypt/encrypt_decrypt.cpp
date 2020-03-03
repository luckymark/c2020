//直接 ^ 作为加密解密方法吧，毕竟是level1，逃 
#include<stdio.h>
#include<cstring>
const int maxn = 20;

void encrypt_decrypt(const char* to_encrypt, const char* key, char* result){
	for(int i = 0; i< maxn; i++)
		result[i] = to_encrypt[i] ^ key[i%strlen(key)];		//循环比较没毛病 
}


int main(){
	char to_encrypt[maxn], output[maxn], key[maxn];
	printf("请输入不大于%d位的需加密字符串\n", maxn);
	scanf("%s", to_encrypt); 
	printf("请输入不大于%d位的密码，以及密码超过原文部分会被扔掉 狗头\n", maxn);
	scanf("%s", key);
	
	encrypt_decrypt(to_encrypt, key, output);
	printf("加密后字符串为%s\n", output);
	printf("请输入密码解密\n"); 
	scanf("%s", key);		//默默扔掉原来钥匙
	encrypt_decrypt(output, key, to_encrypt);	//默默扔掉原来字符串 
	printf("解密后字符串为%s\n", to_encrypt); 
	return 0;
}
