/*
 * count the blanks, tabs and newlines
 * */

#include <stdio.h>

int main()
{
	int blanks = 0, tabs = 0, newlines =0;
	int input;
	while((input = getchar()) != EOF){
		switch(input){
			case '\t':
				tabs++;
				break;
			case ' ':
				blanks++;
				break;
			case '\n':
				newlines++;
				break;
			default:
				;
		}
	}
	printf("neslines:%d\ttabs:%d\tblanks:%d\n", newlines, tabs, blanks);
}
