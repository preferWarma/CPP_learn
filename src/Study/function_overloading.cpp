/*函数重载的简单举例*/
#include<bits/stdc++.h>
using namespace std;

int calc(int x); //接受一个参数时返回它的平方
int calc(int x,int y); // 接受两个参数时返回他们的积
int calc(int x,int y,int z); //接受三个参数时返回他们的和

int main()
{
	int x,y,z,n=1;
	cout << "请输入最多三个数字，整数之间用空格隔开，以换行结尾" << endl;
	while(n)
	{
		if(n == 1)
			cin >> x;
		if(n == 2)
			cin >> y;
		if(n == 3)
			cin >> z;

		char ch = cin.get();
		if(ch == '\n' || n == 3)
			break;
		n++;
	}
	switch (n)
	{
	case 1:
		cout << calc(x);
		break;
	case 2:
		cout << calc(x,y);
		break;
	case 3:
		cout << calc(x,y,z);
		break;
	
	default: cout << "参数输入有误" << endl;
		break;
	}
	return 0;
}

int calc(int x)
{
	return x * x;
}

int calc(int x,int y)
{
	return x * y;
}

int calc(int x,int y,int z)
{
	return x + y + z;
}
