/*输入若干数据找出最大值,以文件读取为例*/
#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ifstream infile;
	infile.open("1.txt");
	ofstream outfile;
	outfile.open("2.txt");
	if(!infile)
		cout << "文件打开失败！" << endl;
	int max = INT32_MIN;
	int x;
	while(infile >> x)
	{
		if(max < x)
			max = x;
	}
	infile.close();
	outfile << "Max = " << max << endl;
	outfile.close();
	return 0;
}