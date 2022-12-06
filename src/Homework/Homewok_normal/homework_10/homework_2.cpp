/*
设计实现一个函数模板，实现任意数据类型的查找。
*/
#include<iostream>
#include<string>
using namespace std;

template <typename T1, typename T2> int find_any(T1* arr, int n, T2 element) {	//查找任意数据类型的数组，若找到则返回其下标，否则返回-1
	for(int i = 0; i < n; i++) {
		if(arr[i] == element)
			return i;
	}
	return -1;
}

int main() 
{
	string arr[7] = {"I", "really", "like", "you"};
	int index = find_any(arr, 7, "like");
	cout << "index = " << index << endl;
	return 0;
}