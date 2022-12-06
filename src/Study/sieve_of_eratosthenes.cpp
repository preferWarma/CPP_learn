//使用埃拉托斯特尼筛法筛选素数, 时间复杂度o(nlogn)
#include<iostream>
#include<cstring>
using namespace std;
const int N = 10001;
bool isprime[N];		//true为素数, false不为素数

void choose() {
	memset(isprime, true, sizeof(isprime));	//初始化
	isprime[0] = isprime[1] = false;	//0, 1都不是素数
	for(int i = 2; i*i < N; i++) {
		if(isprime[i]) {		//如果是素数, 则它的倍数不是素数
			for(int j = i * 2; j <= N; j += i) {
				isprime[j] = false;
			}
		}
	}
}

int main() 
{
	choose();
	for(int i = 0; i < 100; i++) {
		if(isprime[i]) {
			cout << i << endl;
		}
	}
	return 0;
}