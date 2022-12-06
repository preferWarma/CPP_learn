//insert(size_type pos1, const base_string & str, size_type pos2, size_type n) //使用时至少需要前两个参数，数据被插入到指定位置的前一个位置
//insert(iterator pos , size_type n, charT c)  //在pos前插入n个c字符,n的默认值为1
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str = "Hello";
	str.insert(str.size()," word");
	cout << str << endl;
	str.insert(str.size(),"2!2",1,1);
	cout << str << endl;
	str.insert(str.end(), 2, '0');
	cout << str << endl;
	return 0;
}