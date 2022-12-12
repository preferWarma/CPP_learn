## 优先选用auto, 而非显示声明

1. 在声明迭代器时

```cpp
template<typename It>
void dwim(It b, It e) {
	while (b != e) {
		auto currValue = *b;
	}
}
```
在迭代器所指型别的声明中，如果我们使用显示声明，可能会是如下的样子：

```cpp
typename std::iterator_traits<It>::value_type currValue = *b;
```

2. 在使用lambda表达式时

一个前置知识是：lambda返回的是一个std::function的对象, std::function可以指涉任何可以调用的对象，如果要创建一个std::function对象就必须指明函数参数的类型，这样就会使得代码变得冗长，举一个例子：

```cpp
// 可以这样定义一个func
std::function<bool(const std::unique_ptr<int>&, const std::unique_ptr<int>&)> 
func = [](const std::unique_ptr<int>& lhs, const std::unique_ptr<int>& rhs) {
	return *lhs < *rhs;
};
```

是不是看起来非常的冗长，如果使用auto就会变得简洁很多：

```cpp
auto func = [](const std::unique_ptr<int>& lhs, const std::unique_ptr<int>& rhs) {
	return *lhs < *rhs;
};
```
在C++14中，我们甚至可以使用auto来声明lambda的参数，这样就可以省略掉参数的类型声明：

```cpp
auto func = [](const auto& lhs, const auto& rhs) {
	return *lhs < *rhs;
};
```

3. 避免产生"类型捷径"的代码

```cpp
std::vector<int> v;
unsigned sz = v.size();
```
在C++的标准中,v.size()的返回值应该是std::vector<int>::size_type，它仅仅规定成一个无符号整数，所以会有上述的写法，但是在64位系统中，unsigned和 std::vector<int>::size_type是不一样的，64位系统中的size_type 是unsigned long long，所以在64位系统中，上述的写法就会产生错误，变相的降低了代码的移植性。这时可以使用auto来避免这种情况：

```cpp
std::vector<int> v;
auto sz = v.size();
```

在对map类别进行foreach遍历时会出现另一种可能的隐患

```cpp
std::unordered_map<std::string, int> m;
for (const std::pair<std::string, int>& p : m) {
	// do something
}
```
实际上该unordered_map的迭代器的类型是std::pair<const std::string, int>，但是在遍历时，我们使用的是const std::pair<std::string, int>，这样上述代码就会产生一个从const std::pair<const std::string, int>对象到std::pair<std::string, int>对象的隐式转换，虽然上述代码可以执行，但是会对每一次遍历产生一个临时对象并析构，这样会降低代码的效率，所以我们可以使用auto来避免这种情况：

```cpp
std::unordered_map<std::string, int> m;
for (const auto& p : m) {
	// do something
}
```

从上述例子中可以说明有时候显示声明会产生意想不到的隐式类型转换，虽然auto并不完美，有些初始化表达式的类别其不符合期望也不符合要求，但是在大多数情况下，auto都是一个很好的选择。或许有人认为改用auto后会产生源代码的可读性问题。

这一点并不用我们来操心，首先目前市面上主流的IDE都有显示对象类别的能力，例如支持python这样的无需显示类型声明的语言的pycharm。其次auto是一个可选项，而不是一个必选项，例如对于一个整数的声明或初始化我们可以直接使用int a = 1;而不必使用auto a = 1;，所以我们可以根据自己的需要来选择使用auto还是显示声明。在你的专业判断之下，当你认为此处代码使用显示声明更加清晰且可维护性更高或有其他好处的时候，当然可以继续使用他们。在多数情况下，对于一个型别的抽象的理解可能会更好的有助于我们理解代码的含义，而不是去关心他们的具体的类别。比如知道对象是个容器，或是个智能指针就足够使用了，当然这需要你的变量命名足够规范。

总结：
1. auto变量必须初始化，推导过程在编译期而不是运行期，无需担心推导会造成性能浪费，使用auto可以简化重构流程且可以避免代码冗长
2. 需要自己一定的判断能力