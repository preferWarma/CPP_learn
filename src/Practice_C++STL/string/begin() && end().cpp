//begin()指向第一个元素的迭代器
//end()指向最后一个元素的下一位的迭代器
#include<iostream>
#include<string>
using namespace std;

int main()
{
	string s = "Hello";
	cout << *s.begin() << endl; // 输出第一个字符'H'
	cout << *(s.begin() + 1) << endl; //输出第二个字符'e'
	cout << *(s.end() - 1) << endl; // 输出最后一个字符'o'
	return 0;
}