/*01背包问题*/
#include<bits/stdc++.h>
using namespace std;
void test_2_wei_bag_problem1() {
	vector<int> weight = {1,3,4};
	vector<int> value = {15,20,30};
	int bagWeight = 4;
	//dp[i][j]的含义是从0-i间的任意物品放入空间为j的背包中的最大价值
	vector<vector<int>> dp(weight.size(), vector<int>(bagWeight + 1, 0));
	//初始化
	for(int i = 0; i < weight.size(); i++)
		dp[i][0] = 0;
	for(int j = weight[0]; j <= bagWeight; j++)
		dp[0][j] = value[0];
	//遍历
	for(int i = 1; i < weight.size(); i++){
		for(int j = 1; j <= bagWeight; j++){
			if(j < weight[i])
				dp[i][j] = dp[i -1][j];
			else
				dp[i][j] = max(dp[i - 1][j],dp[i - 1][j - weight[i]] + value[i]);
		}
	}
	cout << dp[weight.size() - 1][bagWeight] << endl;
}

int main()
{
	test_2_wei_bag_problem1();
	return 0;
}