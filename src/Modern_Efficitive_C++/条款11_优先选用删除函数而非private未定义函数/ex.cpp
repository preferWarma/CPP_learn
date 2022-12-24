#include <iostream>

using namespace std;

bool isLucky(int number) {
	return true;
}
bool isLucky(char) = delete;
bool isLucky(bool) = delete;
bool isLucky(double) = delete;

template <typename T>
void processPointer(T* ptr) {
	cout << "OK" << endl;
}
template <>
void processPointer<void>(void*) = delete;
template <>
void processPointer<char>(char*) = delete;
template <>
void processPointer<const void>(const void*) = delete;
template <>
void processPointer<const char>(const char*) = delete;


int main() {
	cout << isLucky(7) << endl;	// OK
	//cout << isLucky('a') << endl;	// 编译错误
	//cout << isLucky(true) << endl;	// 编译错误
	//cout << isLucky(3.14)) << endl;	// 编译错误
	int x = 0;
	processPointer(&x);	// OK
	auto str = "123";
	// processPointer(str);	// 编译错误
	return 0;
}