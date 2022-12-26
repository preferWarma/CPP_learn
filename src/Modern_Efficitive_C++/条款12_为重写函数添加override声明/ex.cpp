#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Base {
public:
	virtual void doWork() const {
		cout << "Base::doWork()" << endl;
	}
	virtual void mfunc_1(int) {
		cout << "Base::mfunc(int)" << endl;
	}
	virtual std::string& getData()& {
		return m_data;
	}
	virtual std::string&& getData()&& {
		return std::move(m_data);
	}
	virtual void mfunc_2(int) const {
		cout << "Base::mfunc_2(int) const" << endl;
	}
private:
	std::string m_data;
};

class Derived: public Base {
public:
	Derived(std::string name = "Derived"): m_data(name) {}
	
	void doWork() const override {
		cout << "Derived::doWork()" << endl;
	}
	void mfunc_1(int) override {
		cout << "Derived::mfunc(int)" << endl;
	}
	std::string& getData()& override {
		return m_data;
	}
	std::string&& getData()&& override {
		return std::move(m_data);
	}
	void mfunc_2(int) const override {
		cout << "Derived::mfunc_2(int) const" << endl;
	}
private:
	std::string m_data;
};

decltype(auto) makeDerived(std::string name) {
	return Derived(name);
}

int main() {
	unique_ptr<Base> p = make_unique<Derived>("Derived");
	p->doWork();
	p->mfunc_1(1);
	p->mfunc_2(1);
	cout << p->getData() << endl;
	cout << makeDerived("makeDerived").getData() << endl;
	return 0;
}