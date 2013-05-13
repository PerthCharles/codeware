/*
 *reverse a string line
 * */

#include <stdio.h>
#include <string.h>

#define LIMIT 100 	//a line should short then 100
int next_line = 1;

int getaline(char * aline)
{
	int i = 0;
	int c = 0;
	while((c = getchar()) !=EOF){
		if(i < LIMIT){
			aline[i] = c;
			i++;
		}
		else{
			printf("a line should short then 100.\n");
		}
		if(c == '\n'){
			aline[i-1] = '\0';
			break;
		}
	}
	if(c == EOF){
		next_line = 0;
	}
	return i;
}

void reverse(char * aline, int length)
{
	int mid = 0, i = 0, tmp = 0;
	mid = length/2;
	printf("length:%d	min:%d\n", length, mid);
	for(i = 0; i < mid; i++){
		tmp = aline[i];
		aline[i] = aline[length - 1 -i];
		aline[length - 1 - i] = tmp;
	}
}

int main()
{
	int length = 0;
	char aline[LIMIT+1];
	memset(aline, '\0', LIMIT+1);
	while(next_line){
		//length = getaline(aline);
		if((length = getaline(aline)) > 0){
			reverse(aline, length - 1);
			printf("%s\n", aline);
		}
	}
}



