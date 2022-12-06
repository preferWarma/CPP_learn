//getline(输入流,接收容器) 将输入流(可以包含空格，以换行结束)的内容传入到接收容器中去
//getline(输入流,接收容器,截止字符) 将输入流(可以包含空格，以换行结束)的内容传入到接收容器中去，如果遇到截止字符则停止
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str;
	getline(cin,str,'?');
	cout << str << endl;
	return 0;
}