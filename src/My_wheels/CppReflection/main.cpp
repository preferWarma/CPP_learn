#include "all.h"

using namespace std;
using namespace lyf::reflect;



int main() {
	ClassFactory* factory = ClassFactory::Instance();
	
	Object* a = factory->create_class("A");
	a->print();
	a->set("m_age", 100);
	a->set("m_name", string{"lyf"});
	auto age = a->get<int>("m_age");
	auto name = a->get<string>("m_name");
	cout << age << endl;
	cout << name << endl;
	
	cout << "-------------------------------------" << endl;
	Object* b = factory->create_class("B");
	b->set("m_age", 200);
	auto name1 = b->get<int>("m_age");
	cout << name1 << endl;
	b->print();
	
	return 0;
}