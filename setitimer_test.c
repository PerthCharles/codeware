#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

struct timeval tv;

void setitimer_test(int signo)
{
	gettimeofday(&tv, NULL);
	printf("tv_sec:%d	tv_usec:%d\n", tv.tv_sec, tv.tv_usec);
}

void main()
{
	struct itimerval timer;
//	struct timezone tz;
	gettimeofday(&tv, NULL);
	//gettimeofday(&tv, &tz);
	printf("main tv_sec:%d	tv_usec:%d\n", tv.tv_sec, tv.tv_usec);

	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 100000;		//100ms

	timer.it_interval.tv_sec = 0;
	//timer.it_interval.tv_usec = 100000;
	timer.it_interval.tv_usec = 0;
	signal(SIGALRM, setitimer_test);
	setitimer(ITIMER_REAL, &timer, NULL);
	while(1){
	}
}
