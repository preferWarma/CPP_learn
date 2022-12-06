/*string类和字符数组的区别，以及cin.get(),getline()的用法*/
#include<bits/stdc++.h>
using namespace std;

int main()
{
	char arr1[10];
	cin.get(arr1,10).get();//等价于cin.get(arr,10); cin.get();这两个语句的合并
	cout << "arr1 = " << arr1 << endl;
	cout << "strlen(arr1) = " << strlen (arr1) << endl;
	string arr2;
	getline(cin,arr2); 
	cout << "arr2 = " << arr2 << endl;
	cout << "arr2.size() = " << arr2.size() << endl; //string类的size函数类似于c风格的strlen函数，返回可见字符串长度(不包括\0)
	return 0;
}