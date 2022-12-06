#pragma once

// #include "../reflect/Object.h"
#include "../reflect/ClassRegister.h"
#include <string>
#include <iostream>

using namespace lyf::reflect;
using Object = lyf::reflect::Object;

class A : public Object {
public:
	A() = default;
	A(std::string name, int age) : m_name(name), m_age(age) {}
	~A() = default;

	void print() {
		std::cout << "A::print()" << std::endl;
	}

public:
	std::string m_name;
	int m_age;
};

REGISTER_CLASS(A);
REGISTER_CLASS_FIELD(A, m_name, std::string);
REGISTER_CLASS_FIELD(A, m_age, int);
