/*
 *剑指offer43题
 *求n个骰子出现点数和为m的概率
 * */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define dice_dim 6
int call_times = 0;

int main()
{
	int n, m;
	int max = 0, tmp;
	unsigned int *appear_times;
	double total;
	double total_check = 0.0;

	void init_array(int *a, int max);
	unsigned int calculate_1(int n, int m);
	unsigned int calculate_2(int n,int m, unsigned int **memo);

	scanf("%d", &n);

	if(n == 0){
		printf("you must be kidding me!\n");
		return 0;
	}
	max = dice_dim * n;
	total = pow(dice_dim*1.0, n);
	printf("total:%.1f max:%d\n", total, max);
	appear_times = (unsigned int *)malloc(sizeof(unsigned int) * max);

	/*definition for calculate_2*/
	unsigned int **memo;
	memo = (unsigned int **)malloc(sizeof(unsigned int *) * n);
	for(tmp = 0; tmp < n; tmp++){
		memo[tmp] = (unsigned int *)malloc(sizeof(unsigned int) * max);
	}

	/*definition for calculate_3*/
	unsigned int *a_1, *a_2;
	int flag = 1;
	a_1 = (unsigned int *)malloc(sizeof(unsigned int) * max);
	a_2 = (unsigned int *)malloc(sizeof(unsigned int) * max);
	for(tmp = 0; tmp < dice_dim; tmp++){
		a_1[tmp] = 1;
//		a_2[tmp] = 1;
	}
	int tmp2, tmp3;
	for(tmp = 2; tmp <= n; tmp++){
		if(flag == 1){
			init_array(a_2, max);
			for(tmp2 = tmp; tmp2 <= tmp * dice_dim; tmp2++){
//				a_2[tmp2 -1] = 0;
//				for(tmp3 = 1; tmp3 <= dice_dim && (tmp2 - 1 - tmp3 >= tmp); tmp3++){
				for(tmp3 = tmp2 - 1; tmp3 >= (tmp - 1) && tmp3 >= tmp2 - 6; tmp3-- ){
				//	a_2[tmp2 - 1] += a_1[tmp2 - 1 - tmp3];
					a_2[tmp2 - 1] += a_1[tmp3 - 1];
				}
			}
			flag = 2;
		}
		else if(flag == 2){
			init_array(a_1, max);
			for(tmp2 = tmp; tmp2 <= tmp * dice_dim; tmp2++){
//				a_1[tmp2 -1] = 0;
				//for(tmp3 = 1; tmp3 <= dice_dim && (tmp2 - 1 - tmp3 >= tmp); tmp3++){
				for(tmp3 = tmp2 - 1; tmp3 >= (tmp - 1) && tmp3 >= tmp2 - 6; tmp3-- ){
					//a_1[tmp2 - 1] += a_2[tmp2 - 1 - tmp3];
					a_1[tmp2 - 1] += a_2[tmp3 - 1];
				}
			}
			flag = 1;
		}
	}

	for(tmp = n; tmp <= max; tmp++){
//		appear_times[tmp - 1] = calculate_1(n, tmp);	
		appear_times[tmp - 1] = calculate_2(n, tmp, memo);	
//		total_check += appear_times[tmp - 1];
		printf("[method one]m:%-20d appear_times:%-20u probability:%-20.16f\n", tmp, appear_times[tmp - 1], appear_times[tmp - 1]/total);
		if(flag == 1)	printf("[method two]m:%-20d appear_times:%-20u probability:%-20.16f\n", tmp, a_1[tmp - 1], a_1[tmp - 1]/total);
		if(flag == 2)	printf("[method two]m:%-20d appear_times:%-20u probability:%-20.16f\n", tmp, a_2[tmp - 1], a_2[tmp - 1]/total);
	}
//	printf("total call times:%d\nIs the total nums right? %s\n", call_times, (total == total_check)? ("Yes"):("No"));
	free(memo);
	free(a_1);
	free(a_2);
	free(appear_times);
	return 0;
}

unsigned int calculate_1(int n, int m)
{
	call_times++;
//	printf("Calling n:%d m:%d\n", n, m);
	int tmp, sum = 0;
	if((m < n) || (m > n * dice_dim) || (n == 0))
		return 0;
	else if(n == 1)
		return 1;
	else{
		for(tmp = 1; tmp <= 6; tmp++){
			sum += calculate_1(n-1, m-tmp);
		}
		return sum;
	}
}

unsigned int calculate_2(int n,int m, unsigned int **memo)
{
	call_times++;
	int tmp, sum = 0;
	if((m < n) || (m > n * dice_dim) || (n == 0))
		return 0;
	else if(n == 1)
		return 1;
	else if(memo[n-1][m-1] != 0)
		return memo[n-1][m-1];
	else{
		for(tmp = 1; tmp <= 6; tmp++){
			sum += calculate_2(n-1, m-tmp, memo);
		}
		return memo[n-1][m-1] = sum;
	}
}

void init_array(int * a, int max)
{
	int i;
	for(i = 0; i < max; i++){
//		printf("%d ", a[i]);
		a[i] = 0;
	}
//	printf("\n");
	return;
}
