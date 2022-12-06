/*介绍延迟函数clock()*/
#include<iostream>
#include<ctime>
using namespace std;

int main()
{
	cout << "请输入延迟时间 : ";
	float secs;
	cin >> secs;
	clock_t delay = secs * CLOCKS_PER_SEC; // clock_t是long通过typedef得到的别名
	cout << "开始\a" << endl;
	clock_t start = clock();
	while(clock() - start < delay);
	cout << "结束" << endl;
	return 0;
}