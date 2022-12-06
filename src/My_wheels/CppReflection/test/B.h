#pragma once

// #include "../reflect/Object.h"
#include "../reflect/ClassRegister.h"

using namespace lyf::reflect;

class B : public Object {
public:
	B() = default;
	~B() = default;

	int add(int a, int b) {
		return a + b;
	}

	void print() {
		std::cout << "B::print()" << std::endl;
	}

public:
	int m_age;
};

REGISTER_CLASS(B);
REGISTER_CLASS_FIELD(B, m_age, int);