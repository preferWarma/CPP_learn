## 为重写函数添加override声明

在派生类中虚函数的实现，会改写基类中对应的虚函数的实现，在这个前提下，虚函数的改写是十分容易出错的

由于“改写”（override）和“重载”（overload）很像，但是两者是完全不相干的概念，正是通过override，使得多态得以实现，可以通过基类接口调用派生类成员函数
```cpp
class Base {
public:
	virtual void doWork();	// 基类中的虚函数
	// ...
};

class Derived : public Base {
public:
	virtual void doWork();	// 改写了Base::doWork(),这里的virtual关键字可以省略
	// ...
};

std::unique_ptr<Base> p = std::make_unique<Derived>();
p->doWork();	// 调用Derived::doWork()
```

override这个动作有以下几个条件：
1. 基类中的函数必须是虚函数
2. 基类和派生类中函数的名字必须完全相同(析构函数除外)
3. 基类和派生类中函数的参数列表必须完全相同
4. 基类和派生类中的函数常量性(constness)必须完全相同
5. 基类和派生类的函数返回值和异常规格必须兼容
除了上述限制以外，C++11又加了一条
6. 基类和派生类的函数引用修饰(reference qualifiers)必须完全相同

引用修饰是为了限制成员函数仅用于左值或右值
```cpp
class Widget {
public:
	void doWork() &;	// 仅用于*this为左值
	void doWork() &&;	// 仅用于*this为右值
};

Widget makeWidget();	// 工厂函数，返回一个右值
Widget w;
w.doWork();	// 调用Widget::doWork() &
makeWidget().doWork();	// 调用Widget::doWork() &&
```

通过上述6条规则我们可以得知，对一个基类的虚函数进行重写是非常容易出错的，而且这个错误很多情况还都是合法的，这样就使得debug变得非常困难。为了避免这种情况，C++11引入了override关键字，这个关键字的作用就是告诉编译器，这个函数是重写了基类的虚函数，如果不是重写的话，编译器就会报错，这样就可以避免上述的错误

```cpp
class Base {
public:
	virtual void mf1() const;
	virtual void mf2(int x);
	virtual void mf3() &;
	void mf4() const;
};

class Derived : public Base {
public:
	void mf1();	// 没有重写，常量性不同
	void mf2(unsigned int x);	// 没有重写，参数列表不同
	void mf3() &&;	// 没有重写，引用修饰不同
	void mf4() const;	// 没有重写，基类的该函数不是虚函数
};
// 上述代码编译器都不会报错，但是这些函数都没有重写基类的虚函数
// 引入override后
class Derived_1 : public Base {
public:
	void mf1() override;	// 编译器报错
	void mf2(unsigned int x) override;	// 编译器报错
	void mf3() && override;	// 编译器报错
	void mf4() const override;	// 编译器报错
};

class Derived_2 : public Base {
public:
	void mf1() const override;	// 正确
	void mf2(int x) override;	// 正确
	void mf3() & override;	// 正确
	// void mf4() const override;	// 编译器报错，基类的该函数不是虚函数
};
```

为改写的函数添加上override声明不仅仅可以让编译器在你想要改写但是实际上没有改写的时候提醒你，它还可以在你打算更改基类虚函数的时候衡量你的改动的波及面，如果你的改动会影响到派生类的话，编译器就会报错，这样就可以避免一些不必要的错误

除了override关键词，C++11还引入了final关键字，这个关键字作用于虚函数的时候会阻止它在派生类中被改写，作用于类的时候，该类禁止作为基类。

总结：
1. 为重写函数添加override声明
2. 成员函数的引用修饰词使得对于左值或右值(*this)的处理能够区分开来

