/*获取当前时间*/
#include<iostream>
#include<ctime>
using namespace std;
int main()
{
	tm*t;
	time_t t1 = time(0);
	t = localtime(&t1);
	cout << t->tm_year + 1900 << endl;		//当前年
	cout << t->tm_mon + 1 << endl;			//当前月
	cout << t->tm_mday << endl;				//当前天
	return 0;
}