/* 设计一个函数print打印字符串，如果只传string型参数s，则字符串长度
跟10比较，大于10，打印前10个字符，小于10，全部输出s；如果传string型参数
s和int型n，则字符串长度跟n比较，大于n，打印前n个字符，小于n，全部输出s。*/
#include<iostream>
#include<string>
using namespace std;

void print(string str,int n = 10)
{
	if(str.size() > n)
	{
		for(int i = 0; i < n; i++)
			cout << str[i];
		cout << endl;
	}
	else
		cout << str << endl;
}

int main()
{
	print("12345678");
	print("It is a long str");
	print("import an int parameter",25);
	print("123456789",6);
	return 0;
}