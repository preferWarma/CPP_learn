//并查集练习题, 国王的烦恼
#include<iostream>
#include<algorithm>
using namespace std;
struct Bridge {			//代表桥
	int a, b, t;		//a,b表示桥连接的两个地方, t表示桥的可用天数
	Bridge() {}
	Bridge(int x, int y, int day) : a(x), b(y), t(day) {}
};
bool cmp(Bridge a, Bridge b) {
	return a.t > b.t;
}
const int N = 10001;
const int M = 100001;
int pre[N];
Bridge bridge[M];
int n, m;
void init() {				//初始化
	for(int i = 0; i < n; i++) {
		pre[i] = i;
	}
}

int find_pre(int key) {		//查
	if(pre[key] == key)
		return key;
	pre[key] = find_pre(pre[key]);
	return pre[key];
}

bool joint(int x, int y) {	//并
	int root_x = find_pre(x);
	int root_y = find_pre(y);
	if(root_x != root_y) {
		pre[root_x] = root_y;
		return true;
	}
	return false;
}


int main() 
{
	cin >> n >> m;
	init();
	int a, b, t;
	for(int i = 1; i <= m; i++) {
		cin >> a >> b >> t;
		bridge[i] = Bridge(a, b, t);
	}
	sort(bridge + 1, bridge + 1 + m, cmp);
	int ans = 0, lastDay = 0;		//lastDay用来存储某个桥的生命时限
	for(int i = 1; i <= m; i++) {
		bool flag = joint(bridge[i].a, bridge[i].b);	//修桥前两个岛未连通返回真，表示连通分量发生了变化
		if(flag && bridge[i].t != lastDay) {	// lastDay为上一次修的桥的寿命，避免一天内计算了多次抗议
			ans++;
			lastDay = bridge[i].t;
		}
	}
	cout << ans << endl;
	return 0;
}