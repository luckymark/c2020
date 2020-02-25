#include <stdio.h>
#include "encrypt_decrypt.h"

int main(int argc, char* argv[])
{
	int choice = -1;
	// 循环 + 菜单
	while (choice)
	{
		printf("程序菜单：\n");
		printf("1）加密\n");
		printf("2）解密\n");
		printf("※其他输入将退出程序\n");
		printf("请输入您的选择：");
		if (scanf_s("%d", &choice) == 1)
		{
			//解决多余输入
			while (getchar() != '\n')
				continue;

			switch (choice)
			{
				case 1:   // 加密
					encrypt();
					break;
				case 2:   // 解密
					decrypt();
					break;
				default:  // 退出程序
					choice = 0;
					break;
			}
		}
		else
			choice = 0;  // 用于退出程序
	}
	printf("感谢您的使用，再见！\n");
	printf("※输入回车退出窗口\n");
	while (getchar() != '\n')
		continue;
	return 0;
}