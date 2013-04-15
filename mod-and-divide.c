/*
 * 编程之美   将帅和问题
 * */

#include <stdio.h>

#define a(i) ( ((i)/9)%3 )
#define b(i) ( ((i)%9)%3 )

#define a2(i) ( (i)/9 )
#define b2(i) ( (i)%9 )

int main()
{
	int i = 81;
	
	while(i--){
		if(a(i) != b(i))
			printf("%d %d\n",a2(i)+1, b2(i)+1);
	}
	return 0;
}
