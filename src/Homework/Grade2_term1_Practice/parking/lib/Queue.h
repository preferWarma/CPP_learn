//链式队列类
#include<iostream>
#include<list>
using namespace std;
template <typename T>	//T为数据类型
class queue {
public:
	queue() {	//默认构造函数
	}
	queue (const queue& q) {	//拷贝构造函数
		this->l = q.l;
	}
	void push(T a) {	//入队
		l.emplace_back(a);
	}
	void pop() {		//出队
		l.pop_front();
	}
	bool empty() {		//是否为空
		return l.empty();
	}
	T front() {			//队头元素
		return l.front();
	}
	T back() {			//队尾元素
		return l.back();
	}
	int size() {
		return l.size();
	}
	T operator[](int n) {
		auto i = l.begin();
		while(n--) i++;
		return *i;
	}
	void erase(T& t) {
		for(auto i = l.begin(); i != l.end(); i++) {
			if(*i == t) {
				l.erase(i);
				return;
			}
		}
	}
private:
	list<T> l;
};
