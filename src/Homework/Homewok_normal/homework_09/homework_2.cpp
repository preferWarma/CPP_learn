#include<iostream>
#include<algorithm>
using namespace std;
class Rational{
public:
	Rational(int a,int b) {				//有参构造函数
		first = a;
		second = b;
		if(b == 0) {
			cout << "分母为0, 输入有误, 程序结束" << endl;
			exit(1);
		}
		in_rational();					//化简
	}
	Rational() {						//默认构造函数
		first = 1;
		second = 1;
	}
	void in_rational() {				//对分数进行有理化
		int &a = first;
		int &b = second;
		if(__gcd(a,b) == 1) {			//如果是有理数
				return;
		}
		else {
			int x = __gcd(a,b);
			a /= x;
			b /= x;
		}
	}

	void print(){						//输出
		if(first == 0) {
			cout << "0" << endl;
			return;
		}
		if(first == second) {
			cout << "1" << endl;
			return;
		}
		cout << first << '/' << second << endl;
	}

	Rational operator +(const Rational number2) {				//重载运算符'+'
		int a = first;
		int b = second;
		int c = number2.first;
		int d = number2.second;
		a = a * d + b * c;
		b = b * d;
		return Rational(a,b);
	}

	Rational operator -(const Rational number2) {				//重载运算符'-'
		int a = first;
		int b = second;
		int c = number2.first;
		int d = number2.second;
		a = a * d - b * c;
		b = b * d;
		return Rational(a,b);
	}

	Rational operator *(const Rational number2) {				//重载运算符'*'
		int a = first;
		int b = second;
		int c = number2.first;
		int d = number2.second;
		a = a * c;
		b = b * d;
		return Rational(a,b);
	}

	Rational operator /(const Rational number2) {				//重载运算符'/'
		int a = first;
		int b = second;
		int c = number2.first;
		int d = number2.second;
		a = a * d;
		b = b * c;
		return Rational(a,b);
	}

	bool operator == (const Rational number2) {				//重载运算符'=='
		if(number2.first == first 
		&& number2.second == second) {
			return true;		
		}
		return false;
	}

private:
	int first;		//分子
	int second;		//分母
};

int main() {
	int a, b;
	cout << "请输入第一个有理数r1的分子和分母: ";
	cin >> a >> b;
	Rational r1(a,b);
	cout << "请输入第二个有理数r2的分子和分母: ";
	cin >> a >> b;
	Rational r2(a,b);
	if(r1 == r2) {
		cout << "r1和r2相同" << endl;
	}
	else {
		cout << "r1和r2不同" << endl;
	}
	cout << "r1 + r2 = ";
	(r1 + r2).print();
	cout << "r1 - r2 = ";
	(r1 - r2).print();
	cout << "r1 * r2 = ";
	(r1 * r2).print();
	cout << "r1 / r2 = ";
	(r1 / r2).print();
	return 0;
}