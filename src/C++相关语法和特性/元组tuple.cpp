#include <iostream>
#include <tuple>

int main()
{
	int size;
	//创建一个 tuple 对象存储 10 和 'x'
	std::tuple<int, char> mytuple(10, 'x');

	//计算 mytuple 存储元素的个数
	size = std::tuple_size<decltype(mytuple)>::value;

	//输出 mytuple 中存储的元素
	std::cout << std::get<0>(mytuple) << " " << std::get<1>(mytuple) << std::endl;

	//修改指定的元素
	std::get<0>(mytuple) = 100;
	std::cout << std::get<0>(mytuple) << std::endl;

	//使用 makde_tuple() 创建一个 tuple 对象
	auto bar = std::make_tuple("test", 3.1, 14);

	//拆解 bar 对象，分别赋值给 mystr、mydou、myint
	const char *mystr = nullptr;
	double mydou;
	int myint;
	//使用 tie() 时，如果不想接受某个元素的值，实参可以用 std::ignore 代替
	std::tie(mystr, mydou, myint) = bar;
	// std::tie(std::ignore, std::ignore, myint) = bar;  //只接收第 3 个整形值
	// C++17中，可以使用结构化绑定来同时定义和获取
	// auto [mystr1, mydou1, myint1] = bar;

	//将 mytuple 和 bar 中的元素整合到 1 个 tuple 对象中
	auto mycat = std::tuple_cat(mytuple, bar);
	size = std::tuple_size<decltype(mycat)>::value;
	std::cout << size << std::endl;
	return 0;
}
