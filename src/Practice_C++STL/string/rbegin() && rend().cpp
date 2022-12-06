//反向迭代器
//rbegin()是begin()的反向迭代器, 等价于end()
//rend()是end()的反向迭代器, 等价于begin()
//rcbegin()和rcend()以此类推
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str = "Hello";
	string::reverse_iterator st1;
	string::reverse_iterator st2;
	//使用rbegin()和rend()进行反向输出
	for(st1 = str.rbegin(),st2 = str.rend(); st1 != st2; st1++) //C++在这里对++运算符进行了重载
	{
		cout << *st1 ;
	}
	cout << endl;
	return 0;
}