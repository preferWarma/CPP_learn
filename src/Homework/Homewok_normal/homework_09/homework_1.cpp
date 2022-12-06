#include <iostream>
#include <cmath>

using namespace std;

class complex {
public:
	complex() {							//默认构造函数
		real = 0.0;
		vir = 0.0;
	}

	complex(float r, float v) {			//有参构造函数
		real = r;
		vir = v;
	}

	float operator ! () {				//重载运算符求模
		return sqrt(real*real + vir*vir);
	}

	complex operator ~ () {				//重载运算符求共轭复数
		return complex(real, -vir);
	}

	bool operator == (const complex c) {	//重载运算符判断是否相同
		if(real == c.real && vir == c.vir)
			return true;
		else
			return false;
	}

	void print() {
		cout << real;
		if(vir > 0)
			cout << "+";
		cout << vir << "i" << endl;
	}
private:
	float real;		//实部
	float vir;		//虚部
};

int main()
{
	complex c1(2,-3);
	c1.print();
	float len = !c1;
	cout << "模长为:" << len << endl;
	complex c2 = ~c1;
	c2.print();
	if(c1 == c2){
		cout << "两复数相同" << endl;
	}
	else
		cout << "两复数不同" << endl;
	return 0;
}