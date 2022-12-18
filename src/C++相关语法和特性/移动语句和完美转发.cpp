#include <cstdarg>
#include <iostream>

inline void print()
{
	std::cout << "\n";
}
// 例: 一个python风格的print函数 (万能引用，可变模板参数，完美转发)
template <typename First, typename... Rest>
inline void print(First &&first, Rest &&...rest)
{
	std::cout << std::forward<First>(first);
	if (sizeof...(rest) == 0)
		std::cout << "\n";
	else
	{
		std::cout << " ";
		print(std::forward<Rest>(rest)...);
	}
}

int main()
{
	print(1, 2, 3, 4, 5);
	return 0;
}