/*
 * 一道二进制反码的问题
 */
#include<stdio.h>
int main(void)
{
	//unsigned char a = 0x25;
	unsigned char a = 0xa5;
	printf("~a(decimal):%d\na(decimal):%d\n\n", ~a, a);
	char b = ~a;
	printf("b(decimal):%d\n~b(decimal):%d\n\n",b,~b);
	unsigned char c = ~a;
	printf("c(decimal):%d\n~c(decimal):%d\n\n",c,~c);
//add for understanding
	printf("a(0x):%x\n~a(0x):%x\nsizeof(unsigned char):%d\nsizeof(char):%d\nsizeof(int):%d\n\n",a,~a, sizeof(unsigned char), sizeof(char), sizeof(int));

	return 0;
}
