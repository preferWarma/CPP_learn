//完全背包问题
#include<iostream>
#include<vector>
using namespace std;

void test_CompletePack()
{
	vector<int> weight = {1,3,4};
	vector<int> value = {15,20,30};
	int weightbag = 4;
	vector<int>dp(weightbag + 1, 0);							//dp[j]表示容量为j的背包的最大价值
	for(int i = 0; i < weight.size(); i++){
		for(int j = weight[i]; j <= weightbag; j++){			//正向遍历，先选质量小的物品，与01背包的区别就在此处
			dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
		}
	}
	cout << dp[weightbag] << endl;
}

int main()
{
	test_CompletePack();
	return 0;
}