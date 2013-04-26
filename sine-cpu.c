/*
 * Control the cpu usage line to show the sina style
 * By Perth Charles
 */
/*
 *If you are going to use gettimeofday() too, please include the correct head file. If you don't, you may found out some weird things, like the usheep won't return
 *correct :(
 */
#include<unistd.h>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<sys/time.h>


#define CYCLE 40	/*the cycle of sine*/
#define INTERVAL 1000	/*the update interval of cpu history, my machine is 1s. Unit of INTERVAL is micro-second*/
#define STEP 80		/*how many dot this function need to simulate in a single CYCLE*/
#define TIMES 20	/*the sina line will show up TIMES times*/
#define PI 3.1415926	/*Life of PI, haha*/

double get_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec*1000.0 + tv.tv_usec*1.0/1000);	// unit is micro-second
}

int main()
{
	double busy[STEP],idle[STEP];//the time need to be busy/idle in a single STEP
	int i,j;
	double begin_a_step;
	int base_line = INTERVAL/2;
	double w = (2*PI)/CYCLE;     //CYCLE = (2*PI)/w when the formula is sin(wx), so you can get it.
	for(i = 0; i < STEP; i++){
		busy[i] = (double)(base_line + base_line*sin(w*i));	//unit of busy and idle is micro-second
		idle[i] = (double)(INTERVAL - busy[i]);
	}
	for(i = 0; i < TIMES; i++){
		for(j = 0; j < STEP; j++){
		//	printf("busy[%d]:%f	idle[%d]:%f\n", j, busy[j], j, idle[j]);
			begin_a_step = get_time();
		//	printf("begin_a_step:%f\n", begin_a_step);
			while((get_time() - begin_a_step) <= busy[j]){
				;
			}
			usleep(idle[j] * 1000);
		}
	}
}
