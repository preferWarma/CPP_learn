#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Cat
{
public:
	Cat(string name = "default name") : name(name) {}
	void speak()
	{
		cout << "Hello, I'm " << name << endl;
	}
	~Cat()
	{
		cout << "Cat " << name << " is destroyed" << endl;
	}

private:
	string name;
};

void pass_value(std::shared_ptr<Cat> value_ptr)
{
	cout << "value use_count : " << value_ptr.use_count() << endl;
}

void pass_reference(std::shared_ptr<Cat> &ref_ptr)
{
	cout << "ref use_count : " << ref_ptr.use_count() << endl;
}

int main()
{
	std::shared_ptr<Cat> shared_p_cat = std::make_shared<Cat>("kitte");
	cout << shared_p_cat.use_count() << endl;
	cout << "---------partition---------" << endl;
	pass_value(shared_p_cat);
	cout << shared_p_cat.use_count() << endl;
	pass_reference(shared_p_cat);
	cout << "------------end------------" << endl;
	return 0;
}
