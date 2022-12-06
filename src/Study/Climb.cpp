//爬楼梯进阶版(完全背包),每次可以爬1-m个阶梯,求爬到楼顶(n)有多少种方法
#include<iostream>
#include<vector>
using namespace std;

int climbStairs(int m, int n){
	vector<int> dp(n + 1, 0);
	dp[0] = 1;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(i >= j)
			dp[i] += dp[i - j];
		}
	}
	return dp[n];
}

int main()
{
	cout << climbStairs(10,100) << endl;
	return 0;
}
