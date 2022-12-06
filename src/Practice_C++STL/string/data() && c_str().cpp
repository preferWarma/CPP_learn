//data()返回指向字符串第一元素的const charT*指针, 相当于返回了与该string类字符串等价的char数组的首地址
//c_str()使用方法与data()基本相同，他们的区别是c_str()以空值字符结尾,而data()只是确保了原来实际存在的字符
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str = "Hello";
	//data()
	const char * p1 = str.data();
	for(p1 = str.data(); *p1!= '\0'; p1++)
	{
		cout << *p1;
	}
	cout << endl;
	//c_str()
	const char * p2 = str.data();
	for(p2 = str.data(); *p2!= '\0'; p2++)
	{
		cout << *p2;
	}
	cout << endl;
	return 0;
}