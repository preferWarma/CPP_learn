//异常处理非法时间的输入
#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

class TimeMistake{
public:
	TimeMistake() {}
	TimeMistake(string s) {
		str = s;
	}
	string get_str() {
		return str;
	}
private:
	string str;
};
void test() throw() {
	cout << "请输入24小时制的时间: " << endl;
	int h, m;
	try {
		scanf("%d:%d", &h, &m);
		if(h < 0 || m < 0)
			throw TimeMistake("输入时间为负数");
		else if(h >= 24)
			throw TimeMistake("输入小时大于等于24");
		else if(m >= 60)
			throw TimeMistake("输入分钟大于等于60");
		else {
			if(h > 12)
				h -= 12;
			else if(h == 0){
				h = 12;
			}
			cout << setw(2) << setfill('0') << h << ':' << setw(2) << setfill('0') << m << endl;
		}
	}
	catch(TimeMistake e) {
		cout << e.get_str() << endl;
	}
	return;
}

int main() 
{
	test();
	return 0;
}