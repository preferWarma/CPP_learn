#include <iostream>
#include <thread>

class Singleton {
public:
	// 获取单例
	static Singleton* GetInstance() {
		return pInstance;
	}
	// 释放单例, 进程退出时调用
	static void DeleteInstance() {
		if (pInstance != nullptr) {
			delete pInstance;
			pInstance = nullptr;
		}
	}

	//打印单例的地址
	void print() {
		std::cout << this << std::endl;
	}

	// 禁止拷贝或赋值(使用delete关键字)
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

private:
	// 禁止外部构造和析构
	Singleton() = default;
	~Singleton() = default;

	// 唯一单例对象指针
	static Singleton* pInstance;
};

// 代码一运行就初始化实例, 本身就线程安全
Singleton* Singleton::pInstance = new (std::nothrow) Singleton;

int main() {
	for (int i = 0; i < 10; i++) {
		Singleton::GetInstance()->print();
	}
	return 0;
}