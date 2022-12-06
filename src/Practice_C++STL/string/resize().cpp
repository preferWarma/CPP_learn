//resize(size_type n)将字符串的长度改为n，如果n < size()，则截断字符串至长度为n, 若n > size(), 则多出来的空间以charT(0)中的字符来填充
//resize(size_type n, charT c)与resize(size_type n)用法相同，只是将默认填充字符改为传入的字符c
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str = "Hello";
	str.resize(10); //虽然使用cout不输出charT(0)的内容，但是size()仍然变为10
	cout << "str = " << str << endl;
	cout << "str.size() = " << str.size() << endl;
	str.resize(10,'v'); 
	cout << "str = " << str << endl;
	str.resize(15,'v');
	cout << "str = " << str << endl;
	return 0;
}