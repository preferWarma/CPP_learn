/*设计一个Circle类，有数据成员radius（半径）、成员函数area()，计算圆的面积。构造一个Circle对象进行测试*/
#include<iostream>
using namespace std;
const double pi = 3.1415926;

class Circle
{
public:
	Circle(double x){
		radius = x;
	}
	double erea(){
		return pi*radius*radius;
	}
private:
	double radius;
};

int main()
{
	Circle c(5);
	double s = c.erea();
	cout << "圆的面积是" << s << endl;
	return 0;
}