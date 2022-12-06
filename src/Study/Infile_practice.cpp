/*对文件读取操作的练习*/
#include<bits/stdc++.h>
using namespace std;

int main()
{
	ifstream infile;
	//infile.open("C:\\Users\\2961884371\\Desktop\\Program Text\\C++_VSCode(Base_Learing)\\src\\Study\\hello.txt");
	infile.open("C:/Users/2961884371/Desktop/Program Text/C++_VSCode(Base_Learing)/src/Study/hello.txt");
	if(!infile.is_open())
	{
		cout << "文件打开失败!" << endl;
		exit(EXIT_FAILURE);
	}
	char value;
	int count = 0;
	while(infile.get(value))
	{
		cout << value;
		count ++ ;
	}
	cout << "总共有" << count << "个字符" << endl;
	return 0;
}
