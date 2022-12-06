//max_size()返回string类可存储的最大长度
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str = "Hello";
	cout << "str.max_size() = " << str.max_size() << endl;
	cout << "str.size() = " << str.size() << endl;
	cout << "str.capacity() = " << str.capacity() << endl;
	return 0;
}