#include <iostream>
#include <array>
#include <iterator>
#include <cmath>

constexpr int pow(int base, int exp) noexcept {
	// 快速幂
	if (exp == 0) return 1;
	int result = 1;
	while (exp) {
		if (exp & 1) {	// 奇数
			result *= base;
		}
		base *= base;
		exp >>= 1;
	}
	return result;
}


int main() {
	// constexpr auto arraySize = std::pow(2, 5);	// 编译会出错，std::pow不是constexpr函数
	// 这里去掉constexpr也会出错，constexpr是接口的一部分，传入的参数是编译期常数，那么函数返回值是编译期就确定的
	constexpr auto arraySize = pow(2, 5);
	std::array<int, arraySize> arr;
	for (int i = 0; i < arraySize; ++i) {
		arr[i] = i;
	}
	std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	int n;	std::cin >> n;
	// 这里传入的参数不是编译期常数，所以函数返回值是运行期确定的，可以arraySize2可以去掉constexpr修饰
	auto arraySize2 = pow(2, n);
	std::cout << arraySize2 << std::endl;

	return 0;
}