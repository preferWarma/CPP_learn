//erase(size_type pos = 0, size_type n = npos) //从第pos个位置开始，删除n位字符
//erase(iterator pos) //删除迭代器pos指向的内容，并返回指向下一个元素的迭代器
//erase(iterator first, iterator last) //删除迭代器[first,lat)中的所有元素,返回被删除的最后一个元素的下一个位置的迭代器
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str = "Hello world!";
	str.erase(str.begin(),str.end()); //删除全部
	if(str.empty())
		cout << "字符串为空" << endl;
	str.insert(0,"Hello,world!");
	str.erase(5);
	cout << str << endl;
	return 0;
}