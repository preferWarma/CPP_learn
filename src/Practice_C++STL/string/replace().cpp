//replace(size_type pos, size_type n,const base_string &str) //用str替换指定字符串从起始位置pos开始长度为n的字符串
//replace(const literator pos,size_type n, const base_string &str) //用str替换指定字符串从起始迭代器pos开始长度为n的字符串 
//replace(const literator start, const literator last, const base_string &str) //用str替换迭代器[start,last)间的内容
//replace(size_type pos1, size_type n1, const base_string &str, size_type pos2, size_type n2) //用str从pos2开始的长度为n2的字符串替换指定字符串从起始位置pos1开始长度为n1的字符串
//replace(size_type pos, size_type n1, size_type n2, const charT c) //用n2个c字符形成的字符串替换指定字符串从起始位置pos开始长度为n1的字符串
//其余重载的使用与上面类似
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str = "This @ a text string";
	str.replace(0,4,"123456");
	cout << str << endl;
	str.replace(str.find('@'),1,"is");
	cout << str << endl;
	str.replace(str.begin(),str.end(),"Hello world!");
	cout << str << endl;
	str.replace(0,5,"My?",0,2);
	cout << str << endl;
	str.replace(str.find('!'), str.find('!') + 1, 3, '?');
	cout << str << endl;
	return 0;
}