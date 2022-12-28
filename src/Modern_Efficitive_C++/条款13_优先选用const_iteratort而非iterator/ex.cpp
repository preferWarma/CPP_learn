#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

template <typename C, typename V>
void findAndInsert(C& container,	// 容器中查找targetVal 
	const V& targetVal,	// 查找目标第一次出现
	const V& insertVal)	// 插入insertVal
{
	using std::cbegin, std::cend;
	auto it = std::find(cbegin(container), cend(container), targetVal);
	container.insert(it, insertVal);
}

int main() {
	std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
	findAndInsert(v, 5, 10);
	std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
	return 0;
}