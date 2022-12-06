//并查集练习题: 合根植物
#include<iostream>
using namespace std;
const int MAX = 1000000;
int m, n, k;
int pre[MAX];

void init() {	//初始化
	for(int i = 0; i < m * n; i++) {
		pre[i] = i;
	}
	return;
}

int find_pre(int x) {	//查找根节点
	if(x == pre[x]) {
		return x;
	}
	pre[x] = find_pre(pre[x]);
	return pre[x];
}

void unite(int x, int y) {	//合并
	int root_x = find_pre(x);
	int root_y = find_pre(y);
	if(root_x != root_y) {
		pre[root_x] = root_y;
	}
}

int main(void)
{
	cin >> m >> n >> k;
	init();
	int x, y;
	while(k--) {
		cin >> x >> y;
		unite(x ,y);
	}
	int ans = 0;
	int a[MAX] = {0};
	for(int i = 0; i < n * m; i++) {
		a[find_pre(i)] = 1;
	}
	for(int i = 0; i < n * m; i++) {
		if(a[i] != 0) {
			ans++;
		}
	}
	cout << ans << endl;
	return 0;
}
