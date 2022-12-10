#include <iostream>
#include  "../../My_wheels/lyf.h"
using namespace std;

int main() {
	int a = 1;
	const int ca = 1;
	int& ra = a;
	int* pa = &a;
	cout << lyf::type_class<decltype(a)>::get() << endl;
	cout << lyf::type_class<decltype(ca)>::get() << endl;
	cout << lyf::type_class<decltype(ra)>::get() << endl;
	cout << lyf::type_class<decltype(pa)>::get() << endl;
	return 0;
}