## 现代C++中decltype推导规则

一般来讲，decltype(expr)的结果是和expr的类型一致的
```cpp
const int ci = 0;	// decltype(ci) 是 const int
bool f(const Widget& w);	// decltype(f) 是 bool(const Widget&)
Widget w;	// decltype(w) 是 Widget
vector<int> v;	// decltype(v) 是 vector<int>
v[0];	// decltype(v[0]) 是 int&
```

C++11中，decltype的主要用途就在于声明那些返回值类型依赖于形参类型的函数模板，例如容器的operator[]的返回值一般为T&，使用decltype来计算返回值类别可以很简单易懂
```cpp
template<typename Container, typename Index>
auto authAndAccess(Container& c, Index i) -> decltype(c[i])
{
	// authUser();
	return c[i];
}
```
函数名字之前使用auto可以让我们的返回值类型写在参数列表后面，在指定参数返回值类别的时候我们就可以使用形参了。这样写的好处是，operator[]返回什么类型，我们的函数就对应的返回相应的类型。在C++14之后，你也可以把尾推导省略(即去掉-> decltype(c[i])这部分)，编译器会自动推导出返回值类型

但是这样会产生一个问题，如条款1所述，函数模板在推导的过程中会忽略引用，可能会出现以下情况
```cpp
template<typename Container, typename Index>
auto authAndAccess(Container& c, Index i)
{
	// authUser();
	return c[i];
}
std::deque<int> d;
authAndAccess(d, 0) = 42;	// 会调用operator[]，但是自动推导的返回值是int而不是int&，所以会出错
```
这时我们就需要对返回值实施decltype推导来保证返回值类型与期望的表达式c[i]完全一致,(当然你也可以使用最开始的尾返回推导)
```cpp
template<typename Container, typename Index>
decltype(auto) authAndAccess(Container& c, Index i)
{
	// authUser();
	return c[i];
}
```

decltype(auto)还可以使用在变量声明的场合
```cpp
Widget w;
const Widget& cw = w;
auto myWidget1 = cw;	// myWidget1的类型是Widget
decltype(auto) myWidget2 = cw;	// myWidget2的类型是const Widget&
```

对于我们的authAndAcess函数的第一个参数，我们可以知道这是一个左值引用，他不能接受一个右值，如果我们有以下的需求、
```cpp
template<typename Container, typename Index>
auto authAndAccess(Container& c, Index i)
{
	// authUser();
	return c[i];
}
std::deque<std::string> makeStringDeque();	// 工厂
auto s = authAndAccess(makeStringDeque(), 0);	// 会出错，因为makeStringDeque()返回的是一个右值
``` 
这里的话我们可以使用万能引用来解决这个问题
```cpp
template<typename Container, typename Index>
decltype(auto) authAndAccess(Container&& c, Index i)
{
	// authUser();
	return std::forward<Container>(c)[i];
}
```
本模板中，我们对于操作的容器类型并不了解，下标的返回值也一样不知情，在这种情况下我们遵循原有的下标值类型是合理的，即使用decltype(auto)来作为返回值类型

在decltype作用一个变量名字时,会出现不一样的情况
```cpp
int x = 0;
decltype(x) y;	// y的类型是int
decltype((x)) z = y;	// z的类型是int&
```

另外，decltype也经常用于推导函数指针
```cpp
int f(int);
using pf = decltype(f)*;	// pf是一个f类型的函数指针
// 等价于typedef int (*pf)(int);
```

总结:
1. 绝大多数情况，decltype会得出变量或表达式的类别且不做任何修改
2. decltype((variable))的结果永远是引用
3. C++14以后支持decltype(auto)，它使用的是decltype推导规则