//substr(type_size pos,type_size n = npos) //获取字符串从第pos位开始的长度为n的字符, n的默认值为npos
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str1 = "Hello world";
	string str2 = str1.substr(0,5);
	cout << str2 << endl;
	string str3 = str1.substr(0);
	cout << str3 << endl;
	return 0;
}