#include <iostream>
#include <string>
using namespace std;

class Widget {
public:
	Widget(int a, int b, std::string name): a(a), b(b), name(name) {
		cout << "constructor" << endl;
	}
	Widget(const Widget&& rhs): a(std::move(rhs.a)), b(std::move(rhs.b)), name(std::move(rhs.name)) {
		cout << "move constructor" << endl;
	}

	Widget& operator=(const Widget&& rhs) {
		a = std::move(rhs.a);
		b = std::move(rhs.b);
		name = std::move(rhs.name);
		cout << "move assignment" << endl;
		return *this;
	}

	int getA() const { return a; }
	int getB() const { return b; }
	std::string getName() const { return name; }

private:
	int a, b;
	std::string name;
};


int main() {
	Widget w1{1, 2, "w1"};
	//Widget w2 {w1};	// 编译器报错, 由于显示声明了移动操作，拷贝操作被删除
	Widget w2 {std::move(w1)};	// 移动构造函数
	cout << w1.getA() << " " << w1.getB() << " " << w1.getName() << endl;
	cout << w2.getA() << " " << w2.getB() << " " << w2.getName() << endl;
	return 0;
}