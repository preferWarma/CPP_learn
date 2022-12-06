/*EOF作为结束语的循环*/
#include<iostream>
using namespace std;
int main()
{
	char ch;
	int count = 0; //计数
	cin.get(ch);
	while(cin) //以EOF作为结束符,一般是<CTRL>+<Z>来模拟EOF,基本等价于while(!cin.fail())
	{
		cout << ch;
		++count;
		cin.get(ch);

	}
	cout << endl << count << "characters read" << endl;
	return 0;
}