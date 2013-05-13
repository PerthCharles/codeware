/*
 *Delete the spaces and tabs in the end of each line,
 *Delete the line if the line is full of spaces and tabs.
 * */

#include <stdio.h>
#include <string.h>

#define LIMIT 100	//the length of each line should short then 100
int next_line = 1;	

int getaline(char * aline)
{
	int end = 0;	//you may need to print 0 ~ (end - 1)
	int i = 0;	//the character number in each line
	int c = 0;
//	char aline[LIMIT];
	while((c = getchar()) != EOF && c != '\n'){
		if(i < 100){
			aline[i] = c;
			i++;
			if(c != ' ' && c != '\t'){
				end = i;
			}
		}
		else{
			printf("the line should short then 100.\n");
			return 0;
		}
	}
	if(c == EOF) next_line = 0;
	return end;
}
int main()
{
	char aline[LIMIT];
//	char * aline;
//	aline = (char *)malloc(sizeof(char) * LIMIT);
	memset(aline, 0, LIMIT);
	int end = 0, i;
	while(next_line){
		end = getaline(aline);
		for(i = 0; i < end; i++){
			putchar(aline[i]);
			if(i == end -1) putchar('\n');
		}
		//if(i == end) putchar('\n');
	}
}
