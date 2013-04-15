/*
 *求一个数的二进制表示中1的个数
 *这里设定这个数为uint类型
 * */

#include <stdio.h>

int main()
{
	void calculate(unsigned int a, unsigned int * num);
	unsigned int a,num=0;
	printf("Enter a number here:");
	scanf("%u", &a);
	calculate(a, &num);
	printf("The number you entered %u has %u of 1\n", a, num);
}

void calculate(unsigned int a, unsigned int * num)
{
	while(a){
		a = a & (a - 1);
		(*num)++;
	}
}
