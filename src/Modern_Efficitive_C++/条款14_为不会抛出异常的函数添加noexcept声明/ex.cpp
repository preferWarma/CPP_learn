#include <iostream>
#include <exception>
#include <iterator>

template<class T, size_t N>
void swap(T(&a)[N], T(&b)[N]) noexcept(noexcept(std::swap(*a, *b))) {
	for (size_t i = 0; i < N; ++i) {
		std::swap(a[i], b[i]);
	}
}
template<class T1, class T2>
struct pair {
	pair() = default;
	pair(const T1& t1, const T2& t2): first(t1), second(t2) {}

	void swap(pair& p) noexcept(noexcept(std::swap(first, p.first)) && noexcept(std::swap(second, p.second))) {
		std::swap(first, p.first);
		std::swap(second, p.second);
	}
	T1 first;
	T2 second;
};

int main() {
	// 数组
	int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	int b[10] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	swap(a, b);
	std::copy(std::begin(a), std::end(a), std::ostream_iterator<int>(std::cout, " ")); std::cout << std::endl;
	std::copy(std::begin(b), std::end(b), std::ostream_iterator<int>(std::cout, " ")); std::cout << std::endl;

	// pair
	pair<int, int> p1{1, 2};
	pair<int, int> p2{3, 4};
	p1.swap(p2);
	std::cout << p1.first << " " << p1.second << std::endl;
	std::cout << p2.first << " " << p2.second << std::endl;

	return 0;
}

