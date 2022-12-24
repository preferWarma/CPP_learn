#include <iostream>

class Singleton {
public:
	// 获取单例实例对象
	static Singleton& GetInstance() {
		// 利用局部静态变量实现单例
		static Singleton instance;
		return instance;
	}

	// 打印单例的地址
	void print() {
		std::cout << this << std::endl;
	}

	// 禁止外部拷贝或赋值
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

private:
	// 禁止外部构造和析构
	Singleton() = default;
	~Singleton() = default;
};

int main() {
	for (int i = 0; i < 10; i++) {
		Singleton::GetInstance().print();
	}
	return 0;
}
