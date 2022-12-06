#include<iostream>
#include<vector>
using namespace std;

class set {

public:
	set() {											//初始化构造函数
	}

	set(const vector<int>& nums) {					//初始化构造函数
		for(int a : nums) {
			(*this)(a);
		}
	}

	set(const set& s) {								//复制构造函数
		num = s.num;
	}

	void operator ()(int a) {						//添加一个不重复的元素
		int flag = 0;
		for(int i = 0; i < num.size(); i++) {
			if(num[i] == a) {
				flag = 1;
				break;
			}
		}
		if(!flag)
			num.push_back(a);
	}

	void erase(int a) {								//删除指定元素
		for(int i = 0; i < num.size(); i++) {
			if(num[i] == a) {
				for(int j = i; j < num.size() - 1; j++) {
					num[j] = num[j+1];
				}
				num.resize(num.size()-1);
				return;
			}
		}
		return;
	}

	friend ostream& operator <<(ostream& os, set& s) {	//输出
		for(int a : s.num)
			cout << a << " ";
		return os;
	}

	friend istream& operator >>(istream& is, set& s) {	//输入
		int a;
		while(cin >> a) {
			s(a);			//添加不重复元素
			if(cin.get() == '\n') {
				break;
			}
		}
		return is;
	}

	set& operator *(const set& num2) {					//重载运算符'&'表示交集
		static set result;	//局部变量的引用返回需要加static
		for(int a : num){
			for(int b : num2.num) {
				if(a==b)
					result(a);
			}
		}
		return result;
	}
	
	set& operator +(const set& num2) {					//重载运算符'+'表示并集
		static set result(num);//局部变量的引用返回需要加static
		for(int a : num2.num){
			result(a);		//添加不重复元素
		}
		return result;
	}

	set& operator -(const set& num2) {					//重载运算符'-'表示差集
		static set result(num);//局部变量的引用返回需要加static
		set t = (*this * num2);
		for(int a : t.num) {
			result.erase(a);
		}
		return result;
	}

private:
	vector<int> num;
};

int main() 
{
	set s1;
	set s2;
	set s3;
	cout << "请输入集合s1和集合s2: " << endl;
	cin >> s1 >> s2;
	cout << "集合s1: " << s1 << "\n集合s2: " << s2 << endl;
	cout << "集合s1和s2的并集是 " << s1 + s2 << endl;
	cout << "集合s1对s2的差集是 " << s1 - s2 << endl;
	cout << "集合s1和s2的交集是 " << s1 * s2 << endl;
	return 0;
}