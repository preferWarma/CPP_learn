/*对文件的直接写入*/
#include<bits/stdc++.h>
using namespace std;

int main()
{
	ofstream outfile; //ofstream类可以使用ostream类的全部行为
	outfile.open("hello.txt"); //打开将要写入的文件，如果不存在则创建
	outfile << "hello world!" << endl;
	outfile << "To be better!" << endl;
	outfile << "We will be forever!" << endl;
	outfile.close(); //关闭文件，如果省略，在程序正常结束后会自动关闭
	return 0;
}