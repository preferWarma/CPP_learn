//构造函数和拷贝构造函数和析构函数的调用
#include<bits/stdc++.h>
using namespace std;

class Rectangle
{
public:
	Rectangle(double = 0, double = 0);
	Rectangle(const Rectangle&);
	void displaySide();
	~Rectangle();
private:
	double width, height;
};

Rectangle::Rectangle(double w, double h) {
	width = w;
	height =h;
	cout << "Constructor is called! ->" << this << " ";
	displaySide();
}

Rectangle::Rectangle(const Rectangle& r) {
	width = r.width;
	height = r.height;
	cout << "Copy constructor is called! ->" << this << " ";
	displaySide();
}

Rectangle::~Rectangle() {
	cout << "Destructor is called! ->" << this << " ";
	displaySide();
}

void Rectangle::displaySide() {
	cout << "(" << width << "," << height << ")" << endl;
}

Rectangle expand(Rectangle r) {
	double x = 5 * 2;
	double y = 9 * 2;
	Rectangle rr(x, y);
	return rr;
}

int main()
{
	Rectangle r1(3.5, 4.9);
	Rectangle r2 = r1;
	r2 = expand(r1);
	return 0;
}
