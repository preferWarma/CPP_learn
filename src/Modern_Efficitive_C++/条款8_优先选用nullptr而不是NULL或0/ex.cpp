#include <iostream>
#include <mutex>
#include <memory>

using namespace std;

void f(int) { cout << "f(int)" << endl; }
void f(bool) { cout << "f(bool)" << endl; }
void f(void*) { cout << "f(void*)" << endl; }

class Widget { };

int f1(std::shared_ptr<Widget> p) { return 0;}
double f2(std::unique_ptr<Widget> p) { return 0.0;}
bool f3(Widget* p) { return true; }

using MuxGuard = std::lock_guard<std::mutex>;

template<typename FuncType, typename MuxType, typename PtrType>
decltype(auto) lockAndCall(FuncType func, MuxType& mux, PtrType ptr) {
	MuxGuard g(mux);
	return func(ptr);
}

int main() {
	f(0); // f(int)
	// f(NULL); // 编译出错
	f(nullptr); // f(void*)
	mutex f1m, f2m, f3m;
	auto res1 = lockAndCall(f1, f1m, nullptr);	// 正确
	cout << res1 << endl;
	// auto res2 = lockAndCall(f2, f2m, 0);	// 错误
	// auto res3 = lockAndCall(f3, f3m, NULL);	// 错误
	return 0;
}