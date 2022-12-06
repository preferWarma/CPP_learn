//push_back(const charT c)向字符串末尾追加一个字符c
//pop_back()删除字符串末尾的一个字符

#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str = "H";
	str.push_back('e');
	str.push_back('l');
	str.push_back('l');
	str.push_back('o');
	str.push_back('!');
	cout << str << endl;
	str.pop_back(); //等价于str.erase(str.end() - 1);
	cout << str << endl;
	return 0;
}