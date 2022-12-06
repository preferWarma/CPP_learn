#include "./src/My_wheels/lyf.h"
#include <vector>

template<typename T>
void f(T param) {
	std::cout << "T: " << lyf::type_class<T>::get()
		<< "\tparam: " << Get_Type(param) << std::endl;
}

template<typename T>
void f1(T& param) {
	std::cout << "T: " << lyf::type_class<T>::get()
		<< "\tparam: " << Get_Type(param) << std::endl;
}

void someFunc(int, double) {}

int main() {
	int x = 27;
	const int cx = x;
	const int& rx = x;
	const char* const ptr = "Fun with pointers";
	const char name[] = "J. P. Briggs";
	f(x);
	f(cx);
	f(rx);
	f(ptr);
	f(name);
	f1(name);
	f(someFunc);
	f1(someFunc);
	return 0;
}
