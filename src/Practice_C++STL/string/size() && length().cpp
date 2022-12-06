//size()返回string类的元素个数，等于begin()与end()之间的距离
//length()完全等价于size(),两者的官方文档介绍与汇编代码完全相同
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str = "Hello";
	cout << "str.size() = " << str.size() << endl;
	cout << "str.length() = " << str.length() << endl;
	return 0;
}