#include <stdio.h>
#include <stdlib.h>
#include "encrypt_decrypt.h"


static void input(link**);
static void output(link* );
static void delall(link**);
/*###加密方式：
//  如果是小写字母，转换为大写再右移5位（轮换）
//	如果是大写字母，转换成小写再左移4位（轮换）
//  如果是数字: {9,8,7,6,5,4,3,2,1,0}->{ 5,2,4,7,8,0,1,9,3,6 };----->(解码){4,3,8,1,7,9,0,6,5,2}
//  如果是 空格 则转换成 *
//  如果是 * 则转换成 空格
//  其他字符 不变
*/

void encrypt(void)
{
	// 分配内存，输入字符串
	printf("请输入您需要加密的密码：\n");
	link* head = NULL;
	input(&head);

	// 加密过程
	link* point = head;
	int num[10] = { '5','2','4','7','8','0','1','9','3','6' };
	printf("加密后：\n");
	while (point != NULL) {
		if (point->a >= 'a' && point->a <= 'z')
		{
			point->a -= 32;
			if (point->a >= 'V')
				point->a = point->a - 26 + 5;
			else
				point->a += 5;
		}
		else if (point->a >= 'A' && point->a <= 'Z')
		{
			point->a += 32;
			if (point->a <= 'd')
				point->a = point->a + 26 - 4;
			else
				point->a -= 4;
		}
		else if (point->a >= '0' && point->a <= '9')
		{
			int x = point->a - '0';
			point->a = num[9 - x];
		}
		else if (point->a == ' ')
			point->a = '*';
		else if (point->a == '*')
			point->a = ' ';

		point = point->next;
	}

	// 打印链表
	output(head);

	// 删除分配的内存
	delall(&head);
}

void decrypt(void)
{
	// 分配内存，输入字符串
	printf("请输入您需要解密的密码：\n");
	link* head = NULL;
	input(&head);

	// 解密过程
	link* point = head;
	int dnum[10] = { '4','3','8','1','7','9','0','6','5','2' };
	printf("解密后：\n");
	while (point != NULL) {
		if (point->a >= 'a' && point->a <= 'z')
		{
			point->a -= 32;
			if (point->a >= 'W')
				point->a = point->a - 26 + 4;
			else
				point->a += 4;
		}
		else if (point->a >= 'A' && point->a <= 'Z')
		{
			point->a += 32;
			if (point->a <= 'e')
				point->a = point->a + 26 - 5;
			else
				point->a -= 5;
		}
		else if (point->a >= '0' && point->a <= '9')
		{
			point->a = dnum[point->a - '0'];
		}
		else if (point->a == ' ')
			point->a = '*';
		else if (point->a == '*')
			point->a = ' ';

		point = point->next;
	}

	// 打印链表
	output(head);

	// 释放分配的内存
	delall(&head);
}


/* 分配内存，解决无限输入 */
static void input(link** head)
{
	*head = (link*)malloc(sizeof(link));
	link* last = *head;
	if (last == NULL)
		exit(-1);
	else {
		last->next = NULL;
		while ((last->a = getchar()) != '\n') {
			last->next = (link*)malloc(sizeof(link));
			if (last->next != NULL) {
				last = last->next;
				last->next = NULL; 
			}
			else
				exit(-1);
		}
		last->a = '\0';
	}
}

/* 释放内存 */
static void delall(link** head)
{
	link* point = *head;
	*head = NULL;
	link* point_son;
	while (point != NULL) {
		point_son = point->next;
		free(point);
		point = point_son;
	}
}

/* 打印链表 */
static void output(link* head)
{
	link* point = head;
	while (point != NULL)
	{
		printf("%c", point->a);
		point = point->next;
	}
	printf("\n");
}