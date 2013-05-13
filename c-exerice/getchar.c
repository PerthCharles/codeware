/*
 * 验证布尔表达式getchar() != EOF 的取值是0还是1
 * 需要注意的点
 * 1.getchar()返回值应该用int型接收，否则若用char型，碰到非正常字符集的字符会溢出
 * 2.linux:ctrl+d windows:ctrl+z 在运行时表示EOF
 * 3.在遇到回车符之前，输入的字符会放到缓冲区内直到遇到第一个回车符getchar()才会真正接收字符。最终要的一点：回车符也会被接收，这点要与scanf区分开
 * */

#include <stdio.h>

int main()
{
	int i;
	while((i = getchar()) != EOF){
		printf("i:%d\n", i);
	}
	printf("EOF:%d\n", EOF);
}
