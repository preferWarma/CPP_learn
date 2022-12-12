#include <iostream>
#include <memory>

using namespace std;

int main() {
	unique_ptr<int> p1(new int(1));
	unique_ptr<int> p2(new int(2));
	auto func = [](const auto& lhs, const auto& rhs) {
		return *lhs < *rhs;
	};
	if (func(p1, p2))
		cout << "p1 < p2" << endl;
	else
		cout << "p1 >= p2" << endl;
	return 0;
}
