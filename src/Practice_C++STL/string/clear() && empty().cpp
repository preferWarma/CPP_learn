//clear()清空字符串
//empty()判断字符串是否为空, size()==0则返回true
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str = "Hello";
	cout << "清空前: " << endl;
	if(str.empty())
		cout << "字符串为空" << endl;
	else
		cout << "字符串不为空" << endl;
	str.clear();
	cout << "清空后: " << endl;
	if(str.empty())
		cout << "字符串为空" << endl;
	else
		cout << "字符串不为空" << endl;
	return 0;
}