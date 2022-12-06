/*对文件的直接读取*/
#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;
const int SIZE = 60;
int main()
{
	ifstream infile; //ifstream类可以使用istream类cin的全部行为
	infile.open("hello.txt"); //打开需要读取的文件
	if(!infile.is_open()) //如果打开文件失败
	{
		cout << "文件打开失败！" << endl;
		exit(EXIT_FAILURE); //退出程序
	}
	string str;
	getline(infile,str); // 使用str来读取"hello.txt"文件中的第一行内容
	cout << "str = " << str << endl;
	char ch;
	infile >> ch; //使用ch来读取"hello.txt"文件中的第一个字符,注意此时是从原文件的第二行开始读取，因为第一行已经被读取完毕了
	cout << "ch = " << ch << endl;
	infile.close();
	return 0;
}