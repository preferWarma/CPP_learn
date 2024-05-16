# include "../../My_wheels/lyf.h"

/*
auto createInitList() {
	return { 1, 2, 3, 4, 5 };	// 编译错误：用大括号扩起的列表不提供返回类型
}
*/

template <typename T>
void f1(T param);

template <typename T>
void f2(std::initializer_list<T> param) {
	std::cout << "传参成功" << std::endl;
}

int main() {
	// f1({1,2,3});	// 会出现编译错误，模板参数无法推导出std::initializer_list<int>类型
	f2({1, 2, 3});	// OK

	auto x1 = 27;
	auto x2(27);
	auto x3 = {27};
	auto x4{27};

	std::cout << typeof(x1) << std::endl;
	std::cout << typeof(x2) << std::endl;
	std::cout << typeof(x3) << std::endl;
	std::cout << typeof(x4) << std::endl;

	return 0;
}