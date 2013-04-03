#include <stdio.h>
#include <time.h>

int main()
{
	while(1){
		printf("%u %d\n", time( (time_t *)NULL ), time( (time_t *)NULL) );
		sleep(1);
	}
}
