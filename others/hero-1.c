/*
求连续子数组的最大和
题目详情:
一个整型数组，数组里有正数也有负数。
数组中连续的一个或多个整数组成一个子数组，每个子数组都有一个和，求所有子数组的和的最大值，要求时间复杂度为O(n)。
 
例如输入的数组为1, -2, 3, 10, -4, 7, 2, -5，那么最大的子数组为3, 10, -4, 7, 2，因此输出为该子数组的和18，
请完成函数int MaxSum(int* a,int n)。
答题说明:
当全是负数的情况时，返回最大的那个负数
*/

/*
解题思路：
	初始化变量：
		max = a[0];		//记录最终的最大值
		tmp_sum = 0;		//临时和
	伪代码：
		for i from 0 to n
			tmp_sum += a[i]
			if tmp_sum > max
				max = tmp_sum
			if tmp_sum < 0
				tmp_sum = 0;
		endif
*/

#include <stdio.h>

#define MAX(a, b) ((a) >= (b) ? (a):(b))

int Max_sum(int *a, int n)
{
	int i;
	int max, tmp_sum = 0;
	if(n == 0){
		return 0;
	}
	max = a[0];
	for(i = 0; i < n; i++){
		tmp_sum += a[i];
		max = MAX(max, tmp_sum);
		if(tmp_sum < 0){
			tmp_sum = 0;
		}
	}
	return max;
}

int main()
{
	int a[8] = {1, -2, 3, 10, -4, 7, 2, -5};
	printf("max_sum is:%d\n", Max_sum(a, 8));
	return 0;
}




