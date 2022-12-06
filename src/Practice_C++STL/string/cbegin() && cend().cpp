//cbegin() 返回指向第一个元素的const_iterator
//cend() 返回指向最后一个元素的下一位的const_iterator
/*
这里补充iterator和const iterator和const_iterator的区别: 
{
	iterator 可遍历，可改变所指元素				//即迭代器指向可变，指向内容也可变
	const_iterator 可遍历，不可改变所指元素 	//即迭代器指向可变，指向内容不可变
	const iterator 不可遍历，可改变所指元素 	//即迭代器指向不可变，指向内容可变
}
*/
#include<iostream>
#include<string>
using namespace std;
int main()
{
	string str = "Hello";
	string::const_iterator st1 = str.cbegin();
	string::const_iterator st2 = str.cend(); 
	cout << "cbegin()返回的迭代器指向内容为" << *st1 << endl;
	for(st1 = str.cbegin();st1 != st2; st1++)
	{
		cout << *st1 << endl;
	}
	return 0;
}