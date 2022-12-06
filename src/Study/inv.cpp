//逆元, 解决除法中的取模问题
//(a / b) % mod = (a * inv(b)) % mod = (a % mod * inv(b) % mod) % mod
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 1e9 + 7;

//费马小定理: inv(b) = (b^(mod-2)) % mod
ll qucik_pow(ll a, ll b) {	//快速幂
	ll ans = 1;
	while(b) {
		if(b & 1)	//如果b为奇数
			ans = (ans * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return ans;
}
ll inv(ll a) {
	return qucik_pow(a, mod - 2);
}

int main()
{

	return 0;
}
