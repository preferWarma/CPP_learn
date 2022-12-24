## 优先选用删除函数，而非private未定义函数

当我们想要阻止其他程序员使用某个函数时，只需要不声明该函数即可，但是C++有时候会替你声明函数，比如自动生成的成员函数，本文中目前只考虑拷贝构造函数和赋值运算符函数。C++11以前我们的做法是将这些函数声明为private，并且不去定义它们。
举例来讲，在C++标准库中输入输出流库继承于basic_ios，对输入流和输出流进行复制是不可取的，C++98中的basic_ios的声明如下：
```cpp
template <class charT, class traits = char_traits<charT> >
class basic_ios : public ios_base {
public:
	// ...
private:
	basic_ios(const basic_ios&); // 不可复制
	basic_ios& operator=(const basic_ios&); // 不可赋值
};
```

在C++11中，有了删除函数，使用delete可以使它们标识为删除函数，我们可以将上述代码改为：
```cpp
template <class charT, class traits = char_traits<charT> >
class basic_ios : public ios_base {
public:
	// ...
	basic_ios(const basic_ios&) = delete;
	basic_ios& operator=(const basic_ios&) = delete;
	// ...
};
```

使用delete关键字和将函数声明为private看起来只是不同风格的选择，但实际上是有区别的。
1. 使用delete删除的函数无法通过任何方法调用，即使是成员函数或友元函数中的代码也是无法调用的。相对于private的做法来讲，这是一种改进。
2. 删除函数往往被声明为public。这样做的好处是，当客户代码尝试调用某个成员函数时，C++会先校验其可访问性，后校验删除状态。这么一来，当客户代码尝试调用某个private函数，编译器只会提示该函数为private。所以把新的delete函数声明为public会得到更好的错误信息。
3. 任何函数都可以成为删除函数，但是只有成员函数才能被声明为private。

举例来讲，如果我们有一个函数bool isLucky(int number);C++中很多类型可以隐式转换到int中，所以会出现以下无意义的代码调用
```cpp
if (isLucky('a')) ...
if (isLucky(true)) ...
if (isLucky(3.14)) ...
```

当我们想要阻止这样的调用的时候，我们可以通过delete关键字来删除对应的重载版本
```cpp
bool isLucky(int number);
bool isLucky(char) = delete;
bool isLucky(bool) = delete;
bool isLucky(double) = delete;
```
这样再出现上述调用的时候，编译器会提示上述函数已经删除，无法调用。

4. 删除函数还可以阻止那些不应该进行的模板实现。

举例来讲，如果你需要一个和内建指针协作的模板
```cpp
template <typename T>
void processPointer(T* ptr) {
	// ...
}
```
而指针的类型中有两个异类，一个是void*，因为无法对它实现自增自减等操作，一个是char*，它是C风格的字符串，而不是指向单个字符的指针。这时候我们可以通过删除函数来阻止对这两种类型的模板实现,而这一点是private无法做到的。
```cpp
template <>
void processPointer<void>(void*) = delete;
template <>
void processPointer<char>(char*) = delete;
template <>
void processPointer<const void>(const void*) = delete;
template <>
void processPointer<const char>(const char*) = delete;
```

总结：
1. 优先选用删除函数，而非private未定义的函数
2. 任何函数都可以被删除，包括非成员函数和模板函数