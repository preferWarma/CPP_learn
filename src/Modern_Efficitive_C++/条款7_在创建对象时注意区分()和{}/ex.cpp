#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main() {
	vector<int> v1(10, 5);
	copy(v1.begin(), v1.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
	vector<int> v2{10, 5};
	copy(v2.begin(), v2.end(), ostream_iterator<int>(cout, " "));
	return 0;
}