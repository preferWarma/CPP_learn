// 举例: A类中有一个需求需要存储其他A类对象的信息

#include <iostream>
#include <memory>

using namespace std;

class Cat
{
public:
	Cat(std::string name = "default name") : name(name)
	{
		cout << "Cat : " << name << " constructor" << endl;
	}
	void speak()
	{
		std::cout << "Hello, I'm " << name << std::endl;
	}
	~Cat()
	{
		std::cout << "Cat " << name << " is destroyed" << std::endl;
	}

	void setName(std::string &name)
	{
		this->name = name;
	}

	void setLiaison(std::shared_ptr<Cat> liaison)
	{
		this->liaison = liaison;
	}

private:
	std::string name;
	// std::shared_ptr<Cat> liaison;	//会出现循环引用
	std::weak_ptr<Cat> liaison; //不会出现循环引用
};

int main()
{
	shared_ptr<Cat> c1 = make_shared<Cat>("c1");
	shared_ptr<Cat> c2 = make_shared<Cat>("c2");
	/*这种情况下，如果Cat的成员变量是shared_ptr就会出现循环引用的问题, 解决办法就是使用weak_ptr*/
	c1->setLiaison(c2);
	c2->setLiaison(c1);
	return 0;
}