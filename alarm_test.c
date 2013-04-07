#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

void test_alarm(int sign_no)
{
	printf("alarm begins at %u\n", time((time_t *)NULL));
	printf("alarm ends   at %u\n", time((time_t *)NULL));
}

int main()
{
	void test_alarm(int sign_no);
	printf("Main begins at %u\n", time((time_t *)NULL));
	signal(SIGALRM, test_alarm);
	alarm(5);
	int i;
	/*if you sleep(10) at once, you may get confused by Main ends at the same time alarm ends, 
 * 	  cause the sleep() function will quit when the process get an signal.
 * 	  if you print the return value, you will find out the details ^_^*/
	for(i=10; i>0; i--){
		sleep(1);
	}
	printf("Main ends   at %u\n", time((time_t *)NULL));
}

