/*输出日历*/
#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
	int day,stop;
	cout << "请输入需要显示的日历月的天数: " << endl;
	cin >> stop;
	cout << "请输入需要显示的月数的第一天起始位置(周几): " << endl;
	cin >> day;
	cout << "  sun" << "  Mon" << "  Tue" << "  Wed" << "  Thu" << "  Fri" << "  Sat" << endl; 
	for(int i = 0; i < day; i++)
		cout << "  " << "   ";
	for(int i = 1; i <= stop; i++)
	{
		cout << "  "  << setw(3) << i; //设置域宽为3
		if((i + day)%7 == 0)
			cout << endl;
	}
	return 0;
}