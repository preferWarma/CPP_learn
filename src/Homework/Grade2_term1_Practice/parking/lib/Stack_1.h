//顺式栈类
#include<iostream>
#include<vector>
using namespace std;
template<typename T>
class stack {
public:
	stack() {
	}
	stack(const stack& s) {
		this->v = s.v;
	}
	void push(T a) {
		v.emplace_back(a);
	}
	void pop() {
		v.pop_back();
	}
	bool empty() {
		return v.empty();
	}
	T top() {
		return v.back();
	}
	int size() {
		return v.size();
	}
	T operator[] (int n) {
		return v[n];
	}
private:
	vector<T> v;
};