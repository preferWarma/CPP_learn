## 在创建对象时注意区分()和{}

C++11中进行对象初始化带来了更丰富的选择，常用的有如下三种方法：
```cpp
int x(0);
int y = 0;
int z{0};
```
很多情况下，使用等号和一对大括号也是可以的:
```cpp
int x = {0};
```
但是并不推荐这种用法，一个等号的加入会让一些人认为其中发生了一次赋值，实际上是没有的。

在C++11引入了统一初始化，既大括号初始化，它可以表达之前无法表达的事情，尤其是对于指定容器的初始化变得非常简单，比如：
```cpp
std::vector<int> v{1, 2, 3, 4, 5};
```
大括号同样可以用来为非静态成员函数指定默认值
```cpp
class Widget
{
public:
	Widget() = default;
	Widget(int a, int b) : m_a(a), m_b(b) {}
private:
	int m_a{0};	// 可行
	int m_b = 0;	// 可行
	// int m_c(0);	// 不可行
};
```
对于不可复制的对象，比如std::atomic，它可以采用大括号和小括号来进行初始化，但是不能使用等号
```cpp
std::atomic<int> a{0};	// 可行
std::atomic<int> b(0);	// 可行
// std::atomic<int> c = 0;	// 不可行
```
通过上述的对比我们就可以知道为什么说大括号是统一的初始化方式了，只有大括号初始化可以适用于所有的场合。

大括号初始化还有一项新特性，就是它禁止内建类型之间的隐式窄化类型转换，比如：
```cpp
int x{3.14};	// 编译错误,大括号中的double不能隐式转换为int
```
而采用小括号或者等号就不存在隐式转换的检查
```cpp
int x(3.14);	// 正确，小括号中的double可以隐式转换为int
int y = 3.14;	// 正确，等号中的double可以隐式转换为int
```
大括号初始化的另一项特性是避免解析语法歧义，比如当你想要以默认构造的方式初始化一个对象，很可能会不小心声明成了一个函数声明，比如：
```cpp
Widget w();	// 这是一个函数声明，而不是对象初始化
```
而使用大括号就可以避免这种歧义
```cpp
Widget w{};	// 这是一个对象初始化
```
但是大括号初始化也有缺陷，在与带有std::initializer_list构造函数的类一起使用时，大括号初始化会导致一些意外行为，比如：
```cpp
class Widget{
public:
	Widget() = default;
	Widget(int i, bool b) {}
	Widget(int i, double d) {}
	Widget(std::initializer_list<long double> il) {}
};

Widget w1(10, true);	// 调用Widget(int i, bool b)构造函数
Widget w2{10, true};	// 调用的是Widget(std::initializer_list<long double> il)构造函数，10和true被强制转化为long double
Widget w3(10, 5.0);	// 调用Widget(int i, double d)构造函数
Widget w4{10, 5.0};	// 调用Widget(std::initializer_list<long double> il)构造函数，10和5.0被强制转化为long double
```
即使是平常会执行的移动构造或者复制构造函数也可能会被带有std::initializer_list构造函数的类所劫持，比如：
```cpp
class Widget{
public:
	Widget() = default;
	Widget(int i, bool b) {}
	Widget(int i, double d) {}
	Widget(std::initializer_list<long double> il) {}
	operator float() const { return 0.0f; }
};

Widget w5(w4); // 调用的是复制构造函数
Widget w6{w4}; // 调用的是Widget(std::initializer_list<long double> il)构造函数，w4的返回值被强制转化为float，然后再被强制转化为long double
Widget w7(std::move(w4));	// 调用的是移动构造函数
Widget w8{std::move(w4)};	// 调用的是Widget(std::initializer_list<long double> il)构造函数，和w6结果一样
```

而这种转化如果是窄向转化的话，就会出现错误
```cpp
class Widget{
public:
	Widget() = default;
	Widget(int i, bool b) {}
	Widget(int i, double d) {}
	Widget(std::initializer_list<bool> il) {}
};

Widget{10, 5.0};	// 编译错误，10和5.0被强制转化为bool,而窄化转化是不允许的
```

还有一个注意的点，当Widget既有默认构造函数，又有带有std::initializer_list构造函数的时候，语言规定空的大括号初始化执行的是默认构造函数，而不是空的std::initializer_list构造函数

总结：
1. 大括号初始化应用最广泛，可以组织隐式窄化类型转换，还可以避免解析语法歧义
2. 在构造函数选择的期间，只要有任何可能的带有std::initializer_list构造函数的类，大括号初始化就会被优先选择，即使是移动构造或者复制构造函数也可能会被带有std::initializer_list构造函数的类所劫持
3. 使用大括号还是小括号有时候会造成大相径庭的结果，比如采用两个实参初始化一个std::vector