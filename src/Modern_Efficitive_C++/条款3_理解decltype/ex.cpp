#include <iostream>
#include "../../My_wheels/lyf.h"

using namespace std;

template<typename Container, typename Index>
decltype(auto) authAndAccess(Container&& c, Index i) {
	// authUser();
	return std::forward<Container>(c)[i];
}

int main() {
	vector<int> v{ 1,2,3,4,5 };
	cout << typeof(authAndAccess(v, 2)) << endl;
	int x = 0;
	cout << typeof(x) << endl;
	cout << typeof((x)) << endl;
	return 0;
}