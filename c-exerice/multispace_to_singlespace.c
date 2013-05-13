/*复制输入到输出，同时将多个连续空格用一个空格代替*/

#include <stdio.h>

int main()
{
	int c, last_c;
	last_c = 'a';  //initalize by non-space

	while((c = getchar()) != EOF){
/*
		if(c == ' '){
			if(last_c != ' '){
				putchar(c);
			}
		}
		else{
			putchar(c);
		}
*/
		if(c != ' ' || last_c != ' '){
			putchar(c);
		}
		last_c = c;
	}
}


