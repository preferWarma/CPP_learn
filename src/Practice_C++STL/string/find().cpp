//find(const base_string & str, size_type pos = 0) //从第pos位(默认值为0)寻找字符str,查找成功则返回str第一次出现时的第一个元素所在位置，否则返回npos;
//find(const charT *s, size_type pos = 0) //从第pos位寻找s指向的字符串，查找成功则返回指向s指向字符串第一次出现时的首字符所在位置，否则返回npos;
//find(const charT *s, size_type pos = 0, size_type n) //从第pos位的后n位寻找s指向的字符串，查找成功则返回指向s指向字符串第一次出现时的首字符的位置，否则返回npos
//find(const charT c, size_type pos = 0) ////从第pos位寻找字符c，查找成功则返回指向c第一次出现时的所在位置，否则返回npos;
//rfind()的用法与find()类似，区别在于rfind()返回的是指向被查找字符串的最后一次出现时首字符的所在位置
//补充: npos被宏定义为-1，但是由于find()函数输出的类型是size_type属于无符号类型，所以输出结果应该位size_type的最大整数值
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str = "Hello";
	cout << str.find('H') << endl;
	cout << str.find('H',1) << endl;
	cout << str.find("ell") << endl;
	cout << str.rfind("ell") << endl;
	cout << str.find('l') << endl;
	cout << str.rfind('l') << endl;
	return 0;
}