#include <iostream>
#include <memory>
#include <map>

using UPtrMapSS = std::unique_ptr<std::map<std::string, std::string>>;

using pfunc = void(*)(int);

void f(int a) {
	std::cout << a << std::endl;
}

int main() {
	UPtrMapSS uptrMapSS = std::make_unique<std::map<std::string, std::string>>();
	uptrMapSS->insert(std::make_pair("a", "b"));
	std::cout << uptrMapSS->at("a") << std::endl;

	pfunc pf = f;
	pf(1);
	return 0;
}