// [外部变量访问方式说明符](参数) mutable noexcept / throw()->返回值类型{函数体;};
#include <iostream>
#include <algorithm>
using namespace std;

//全局变量
int all_num = 0;

int main()
{
	int num[4] = {4, 2, 3, 1};
	//对 a 数组中的元素进行排序
	sort(num, num + 4, [](int x, int y)
		 { return x < y; });

	for (int n : num)
	{
		cout << n << " ";
	}

	// display 即为 lambda 匿名函数的函数名
	auto display = [](int a, int b) -> void
	{ cout << a << " " << b; };
	display(1, 2);

	//局部变量
	int num_1 = 1;
	int num_2 = 2;
	int num_3 = 3;

	cout << "lambda1:\n";
	auto lambda1 = [=] // 值传递全部的局部变量
	{
		//全局变量可以访问甚至修改
		all_num = 10;
		//函数体内只能使用外部变量，而无法对它们进行修改
		cout << num_1 << " "
			 << num_2 << " "
			 << num_3 << endl;
	};
	lambda1();
	cout << all_num << endl;

	cout << "lambda2:\n";
	auto lambda2 = [&] // 引用传递全部的局部变量
	{
		all_num = 100;
		num_1 = 10;
		num_2 = 20;
		num_3 = 30;
		cout << num_1 << " "
			 << num_2 << " "
			 << num_3 << endl;
	};
	lambda2();
	cout << all_num << endl;
	return 0;
}
