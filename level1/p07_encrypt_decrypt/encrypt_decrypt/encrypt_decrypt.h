#ifndef ENCRYPT_DECRYPT
#define ENCRYPT_DECRYPT


typedef struct __LINK__ {
	char a;
	__LINK__* next;
} link;

/* 加密函数 */
void encrypt(void);
/* 解密函数 */
void decrypt(void);



#endif