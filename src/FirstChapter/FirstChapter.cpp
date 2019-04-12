
#include <stdio.h>
#include <stdint.h>

// 起泡排序
void bubble_sort(int32_t arr[], int32_t length)
{
	bool sort_flag = false;
	while (!sort_flag)
	{
		sort_flag = true;
		for (int32_t i = 1; i < length; i++)
		{
			if (arr[i-1] > arr[i])
			{
				int32_t tmp = arr[i-1];
				arr[i - 1] = arr[i];
				arr[i] = tmp;
				sort_flag = false;
			}
		}
		length--;
	}
}

// 统计非负整数的二进制中1的个数
void countOne(uint32_t num)
{
	int32_t count = 0;
	uint32_t tmpNum = num;
	while (0 < num)
	{
		count += (num & 1);
		num >>= 1;
	}
	printf("%u二进制中包含%d个1\n", tmpNum, count);
}

// 计算指数2^n
void cal2n(uint32_t n)
{
	int32_t value = 1;
	uint32_t tmpN = n;
	while (0 < n--)
		value <<= 1;

	printf("2的%d次方:%d\n", tmpN, value);
}

// 线性递归版本计算数组和
int32_t sumArray(int32_t arr[], int32_t length)
{
	if (1 > length )
		return 0;
	return sumArray(arr, length - 1) + arr[length-1];
}

// 倒置数组
void reverse(int32_t arr[], int32_t start, int32_t end)
{
	/* 递归版
	if (start < end)
	{
	int32_t tmp = arr[start];
	arr[start] = arr[end];
	arr[end] = tmp;

	reverse(arr, start + 1, end - 1);
	}*/

	// 迭代版
	while (start < end)
	{
		int32_t tmp = arr[start];
		arr[start] = arr[end];
		arr[end] = tmp;

		start++;
		end--;
	}
}

void reverseArray(int32_t arr[], int32_t length)
{
	reverse(arr, 0, length-1);
}

// 斐波拉契数列
// 0 1 1 2 3 5 8 13 21 ...
//     f g
// 求解第n项值
// 制表法计算
int32_t fib(int32_t n,int32_t &preV)
{
	if (n == 0)
	{
		preV = 1;
		return 0;
	}

	int32_t prepreV = 0;
	preV = fib(n - 1, prepreV);
	return prepreV + preV;
}

// 动态规划
int32_t fib(int32_t n)
{
	int32_t g = 1, f = 0;
	while (0 < n--)
	{
		g += f;
		f = g - f;
	}

	return f;

	//int32_t g = 1, f = 0;
	//int32_t tmpN = n;
	//while (0 < n--)
	//{
	//	if (n % 2 != 0) // 偶数
	//		f = f + g;
	//	else
	//		g = g + f;
	//}
	//
	//if (tmpN % 2 == 0)
	//	return f;
	//return g;
}

int main(int argc, char *argv[])
{
	int32_t arr[] = {3,4,3,1,9,7};
	bubble_sort(arr, 6);

	int32_t sum = sumArray(arr, 6);
	printf("数组和:%d\n",sum);

	reverseArray(arr, 6);

	countOne(7);

	cal2n(11);

	int32_t preV = 0;
	int32_t value = fib(3,preV);

	fib(8);

	getchar();
	return 0;
}