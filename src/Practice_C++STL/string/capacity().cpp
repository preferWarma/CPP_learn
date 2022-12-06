//capacity()返回该字符串在不额外分配空间的情况下可容纳的最大元素数，这个值可能是大于实际的字符数size()
//capacity() - size()的值表示在字符串末尾添加字符时需要额外分配的内存
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str = "Hello";
	cout << "str.capacity() = " << str.capacity() << endl;
	cout << "str.size() = " << str.size() << endl;
	int n = str.capacity() - str.size(); //不额外分配内存时的最大剩余容纳元素数
	while(n--)
	{
		str.push_back('1');
	}
	cout << "填充剩余空间后: " << endl;
	cout << "str.capacity() = " << str.capacity() << endl;
	cout << "str.size() = " << str.size() << endl;
	return 0;
}