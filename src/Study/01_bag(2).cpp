//01背包问题(一维DP数组实现)
#include<bits/stdc++.h>
using namespace std;
void test_1_wei_bag_problem1() {
	vector<int> weight = {1,3,4};
	vector<int> value = {15,20,30};
	int bagWeight = 4;
	//DP[j]表示背包空间为j时的最大价值
	vector<int> dp(bagWeight + 1, 0);
	for(int i = 0; i < weight.size(); i++){
		for(int j = bagWeight; j >= weight[i]; j--){			//这里采用倒序遍历,保证每个物品只被计算一次
			dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
		}
	}
	cout << dp[bagWeight] << endl;
}

int main()
{
	test_1_wei_bag_problem1();
	return 0;
}