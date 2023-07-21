#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 1.判断一个数列是否严格单调增或者单调减
bool monotonous(int* a, int n) {
	if (n <= 2) {
		return true;
	}
	bool isIncrease = true;
	bool isDecrease = true;
	for (int i = 1; i < n; i++) {
		if (a[i] > a[i - 1]) {
			isDecrease = false;
		}
		if (a[i] < a[i - 1]) {
			isIncrease = false;
		}
	}
	return isIncrease || isDecrease;
}

// 2. 输出一个32位整数的二进制形式有多少个0
int countZero(int n) {
	int count = 0;
	while (n) {
		if ((n & 1) == 0) {
			count++;
		}
		n >>= 1;
	}
	return count;
}

// 3. 给你1个数组, 可以任意交换一次二个位数, 例如可以吧2314交换为1234, 输出能交换出的最小数
int min(int a, int b) {
	return a < b ? a : b;
}
void swap(char* a, char* b) {
	char c = *a;
	*a = *b;
	*b = c;
}
int minimumSwap(int num) {
	char a[8];
	sprintf(a, "%d", num);	// 将数字转换为字符串
	int n = strlen(a);
	int minNum = num;
	// 暴力枚举所有交换的可能
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			swap(a + i, a + j);
			minNum = min(minNum, atoi(a));
			swap(a + i, a + j);
		}
	}
	return minNum;
}

// 4. 给一个无序数组, 重排一个子数组,能使整个数组有序, 输出这个子数组的最小长度
int findUnsortedSubarray(int* a, int n) {
	int minNum = a[n - 1];
	int maxNum = a[0];
	int left = 0;	// 无序子数组的左边界
	int right = -1;	// 无序子数组的右边界
	for (int i = 0; i < n; i++) {
		if (a[i] < maxNum) {
			right = i;
		}
		else {
			maxNum = a[i];
		}
		if (a[n - i - 1] > minNum) {
			left = n - i - 1;
		}
		else {
			minNum = a[n - i - 1];
		}
	}
	return right - left + 1;
}


int main() {
	// int a[] = {1,2,3,4,5,6};
	// int b[] = {6,5,4,3,2,1};
	// int c[] = {1,2,3,4,5,4};
	// int d[] = {6,5,4,3,2,3};
	// printf("%d\n", monotonous(a, 6));	// 1
	// printf("%d\n", monotonous(b, 6));	// 1
	// printf("%d\n", monotonous(c, 6));	// 0
	// printf("%d\n", monotonous(d, 6));	// 0

	// printf("%d\n", countZero(512));	// 512 = 10_0000_0000
	// printf("%d\n", countZero(1024)); // 1024 = 100_0000_0000

	// printf("%d\n", minimumSwap(2314));	// 1324
	// printf("%d\n", minimumSwap(4321));	// 1324

	int a[] = {2, 4, 8, 10, 9, 15};
	int b[] = {1, 2, 3, 4};
	printf("%d\n", findUnsortedSubarray(a, sizeof(a) / sizeof(a[0])));
	printf("%d\n", findUnsortedSubarray(b, sizeof(b) / sizeof(b[0])));

	return 0;
}