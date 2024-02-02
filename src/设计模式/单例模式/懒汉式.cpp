#include <iostream>
#include <string>
#include <vector>
#include <utility>


using std::cin, std::cout, std::endl;
using std::string, std::vector, std::pair;

template <typename T>
class Singleton {	// 泛型单例
public:
	// 获取单例实例对象
	static T& GetInstance() {
		// 利用局部静态变量实现单例
		static T instance;
		return instance;
	}

	// 打印单例的地址
	void printAdress() {
		cout << this << endl;
	}

	// 禁止外部拷贝或赋值
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;

protected:
	// 禁止外部构造和析构
	Singleton() = default;
	~Singleton() = default;
};

class Test : public Singleton<Test> {
public:
	void input() {
		string s; int n;
		while (cin >> s >> n) {
			m_data.push_back({ s, n });
		}
	}

	void output() {
		for (auto& data : m_data) {
			cout << data.first << " " << data.second << endl;
		}
	}
private:
	vector<pair<string, int>> m_data;
};

int main() {
	for (int i = 0; i < 10; i++) {
		Singleton<Test>::GetInstance().printAdress();
	}

	Singleton<Test>::GetInstance().input();
	Singleton<Test>::GetInstance().output();
	return 0;
}
