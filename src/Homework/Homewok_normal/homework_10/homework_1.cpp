/*
实现Set模板类，并重载+、-,<<和>>操作符
*/
#include<iostream>
#include<vector>
using namespace std;

template <typename T> class set {
public:
	set() {			//默认构造函数
	}

	set(vector<T>& nums) {	//有参构造函数
		for(int i = 0; i < nums.size(); i++) {
			(*this)(nums[i]);
		}
	}

	set(const set<T>& s) {	//复制构造函数
		num = s.num;
	}

	void operator ()(T a) {	//重载()来添加一个不重复的元素
		int flag = 0;
		for(int i = 0; i < num.size(); i++) {
			if(a == num[i])	{
				flag = 1;
			}
		}
		if(!flag) {
			num.push_back(a);
		}
	}

	void erase(T a) {	//删除指定元素
		for(int i = 0; i < num.size(); i++) {
			if(num[i] == a) {
				for(int j = i; j < num.size() - 1; j++) {
					num[j] = num[j + 1];
				}
				num.resize(num.size() - 1);
				return;
			}
		}
		return;
	}

	friend ostream& operator <<(ostream& os, set<T>& s) { //重载<<运算符来输出
		for(int i = 0; i < s.num.size(); i++) {
			cout << s.num[i] << " ";
		}
		return os;
	}

	friend istream& operator >> (istream& is, set<T>& s) {//重载>>运算符来输入
		T a;
		while(cin >> a) {
			s(a);
			if(cin.get() == '\n')
				break;
		}
		return is;
	}

	set<T>& operator +(const set<T>& s) { 				//重载+运算符来求并集
		static set<T> result(num);
		for(T a : s.num) {
			result(a);
		}
		return result;
	}

	set<T>& operator -(const set<T>& s) {				//重载-运算符来求差集
		static set<T> result(num);
		for(T a : s.num) {
			result.erase(a);	//删除两集合相同的值，不相同的值不做修改
		}
		return result;
	}
private:
	vector<T> num;
};

int main() 
{
	set<string> s1, s2;
	cout << "请输入s1集合的元素: ";
	cin >> s1;
	cout << "请输入s2集合的元素: ";
	cin >> s2;
	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	cout << "s1 + s2: " << s1 + s2 << endl;
	cout << "s1 - s2: " << s1 - s2 << endl;
	return 0;
}