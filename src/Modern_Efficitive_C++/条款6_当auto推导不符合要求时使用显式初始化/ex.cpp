#include "../../My_wheels/lyf.h"

using namespace std;

class Widget {
};

vector<bool> getFeatures(const Widget w) {
	return vector<bool>(10);
}

int main() {
	auto priority = getFeatures(Widget{})[5];
	cout << Get_Type(priority) << endl;
	return 0;
}