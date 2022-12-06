//链式栈类
#include<iostream>
#include<list>
using namespace std;
template<typename T>
class stack {
public:
	stack() {
	}
	stack(const stack& s) {
		this->l = s.l;
	}
	void push(T a) {
		l.emplace_back(a);
	}
	void pop() {
		l.pop_back();
	}
	bool empty() {
		return l.empty();
	}
	T top() {
		return l.back();
	}
private:
	list<T> l;
};