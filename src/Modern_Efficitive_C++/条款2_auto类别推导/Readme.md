## 现代C++中auto推导规则

让我们类比一下函数模板

```cpp
template<typename T>
void f(ParamType param);

// 当我们使用auto来声明变量的时候，auto就扮演函数模板中的T，变量类型就是ParamType
auto x = expr;
const auto cx = expr;
const auto& rx = expr;
```

所以auto也对应着和函数模板一样的三种情况，推导方式也是一样的
1. 类别修饰符是一个指针或者引用, 但不是万能引用
2. 类别修饰符是一个万能引用
3. 类别修饰符既不是一个指针也不是一个引用

只有一处不同。当我们要声明一个int类型的变量，并将其初始化为27的时候，我们可以这样写

```cpp
// C++11以前
int x1 = 27;
int x2(27);
// C++11之后新增的列表初始化
int x3{27};
int x4 = {27};

// 当我们将声明全部改为auto时候
auto x1 = 27;
auto x2(27);
auto x3{27};
auto x4 = {27};
/*结果与固定类型声明却不一样，对于后面两个语句，编译器会将其推导为std::initializer_list<int>
所以当auto声明变量的初始化表达式是{}包围的列表时，编译器会将其推导为std::initializer_list<T>，其中T是列表中元素的类型*/
```

!!! warning
	在C++的后续版本中，使用auto x = {27}声明的x则是std::initializer_list< int>类型，但是使用auto x{27}声明的x仍未int类型，同时不允许使用auto x{1, 2, 4, 5}这样的语句，如需使用，必须使用auto x = {1, 2, 4, 5}这样的语句

对于大括号初始化表达式的表达方式，是auto类型推导和模板推导的唯一不同之处。auto可以推导出std::initializer_list<T>，但是模板不能，并且会出现编译错误

```cpp
template<typename T>
void f(T param);

f({1, 2, 3}); // 编译错误
auto x = {1, 2, 3}; // 正确

如果我们想要让模板推导出正确的类型，则需要使用std::initializer_list<T>作为模板参数
template<typename T>
void f(std::initializer_list<T> param);

f({1, 2, 3}); // 正确
```

但是对于C++14之后的版本，auto允许作为函数返回值，而且在lamba表达式声明形参的时候也会用到auto，然而这些地方auto的用法是使用的模板推导，而不是auto类型推导

```cpp
// C++14之后
auto createInitList() {
	return {1, 2, 3};	// 错误
}

std::vector<int> v;
auto f = [&v](const auto& newValue) { v = newValue; };
f({1, 2, 3});	// 错误
```

总结：
1. 一般情况下，auto推导和模板推导是一样的，但是auto在遇到诸如auto x = {1, 2, 3}这样的用大括号扩起来的初始化表达式时，会推导为std::initializer_list<T>，而模板则不会

2. auto在函数返回值和lambda表达式中的形参声明中，使用的是模板推导，而不是auto类型推导