/*实现一个有理数类，含构造函数, 输出函数，支持通过运算符重载进行加减乘除的运算*/
//主函数是对类的正确性的简单验证，为突出核心代码，我把类的成员函数实现写在类里
#include<iostream>
#include<algorithm>
using namespace std;
class Rational{
public:
	Rational(int a,int b){				//初始化函数
		number.first = a;
		number.second = b;
	}
	Rational(){
		number.first = 1;
		number.second = 1;
	}
	void in_rational(){					//对分数进行有理化
		int &a = number.first;
		int &b = number.second;
		if(__gcd(a,b) == 1){			//如果是有理数
				return;
		}
		else{
			int x = __gcd(a,b);
			a /= x;
			b /= x;
		}
	}
	void print(){						//输出
		in_rational();
		cout << number.first << '/' << number.second << endl;
	}
	Rational operator +(const Rational number2){				//重载运算符'+'
		int a = number.first;
		int b = number.second;
		int c = number2.number.first;
		int d = number2.number.second;
		a = a * d + b * c;
		b = b * d;
		return Rational(a,b);
	}
	Rational operator -(const Rational number2){			//重载运算符'-'
		int a = number.first;
		int b = number.second;
		int c = number2.number.first;
		int d = number2.number.second;
		a = a * d - b * c;
		b = b * d;
		return Rational(a,b);
	}
	Rational operator *(const Rational number2){			//重载运算符'*'
		int a = number.first;
		int b = number.second;
		int c = number2.number.first;
		int d = number2.number.second;
		a = a * c;
		b = b * d;
		return Rational(a,b);
	}
	Rational operator /(const Rational number2){			//重载运算符'/'
		int a = number.first;
		int b = number.second;
		int c = number2.number.first;
		int d = number2.number.second;
		a = a * d;
		b = b * c;
		return Rational(a,b);
	}
private:
	pair<int,int>number;				//定义pair变量number存储分数，第一个参数是分子，第二个参数是分母
};

int main()
{
	Rational n1(6,15);		//2/5
	Rational n2(1,3);		//1/3
	(n1 + n2).print();		//11/15
	(n1 - n2).print();		//1/15
	(n1 * n2).print();		//2/15
	(n1 / n2).print();		//6/5
	return 0;
}