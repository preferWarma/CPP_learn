#include <iostream>
#include <vector>
#include <mutex>
#include <thread>
using namespace std;

class Polynomial {
public:
	using RootType = std::vector<double>;	// 根的类型

	RootType roots() const {
		std::lock_guard<std::mutex> g(m);	// 保证互斥访问
		if (!rootsAreValid) {
			rootsAreValid = true;
			// rootsVals = ...;	// 计算根
		}
		return rootsVals;
	}

private:
	mutable std::mutex m;	// 互斥量
	mutable bool rootsAreValid{false};	// 缓存根的有效性
	mutable RootType rootsVals;	// 根的值
};

int main() {
	// 创建两个线程, 分别调用roots()函数
	Polynomial p;
	std::thread t1([&p] {
		auto r = p.roots();
	for (auto i : r) {
		cout << i << endl;
	}
		});
	std::thread t2([&p] {
		auto r = p.roots();
	for (auto i : r) {
		cout << i << endl;
	}
		});
	t1.join();	// 等待线程结束
	t2.join();	// 等待线程结束

	return 0;
}

