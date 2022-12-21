## 优先选用nullptr, 而不是NULL或0

直接开门见山摆事实， 字面常量0的类型是int，而非指针，C++在只能使用指针的语境发现一个0会把它解释为空指针，而NULL也无非是0的一个宏罢了，它们本身都不具备指针类型，所以当作为形参传递的时候会与int混淆
在C++11以前，NULL的定义无非以下几种
```cpp
#define NULL 0
#define NULL 0LL
#define NULL (void *)0
```
所以在调用时会出现很多问题

```cpp
void f(int);
void f(bool);
void f(void *);

f(0); // 调用f(int)
f(NULL); // 会出现编译错误
```
在C++11中引入的nullptr并非一个整数，你可以把它理解为任意一种类型的指针, 它可以隐式转换到所有的裸指针类型。对于上述的例子
```cpp
void f(int);
void f(bool);
void f(void *);

f(0); // 调用f(int)
f(nullptr); // 调用f(void *)
```

除了这个优点以外，它还可以提升代码的清晰性，尤其是涉及auto变量的时候，比如
```cpp
auto result = findRecord();
if (result == 0) {
	// do something
}
```
这样对阅读会有歧义，你不知道这个0是一个指针还是一个整数，但是如果是nulllptr就十分清晰，而不会有多义性
```cpp
auto result = findRecord();
if (result == nullptr) {
	// do something
}
```

在涉及到模板的时候，nullptr的优点就更加明显了，比如
```cpp
int f1(std::shared_ptr<Widget> p);
double f2(std::unique_ptr<Widget> p);
bool f3(Widget *p);

//假设调用代码是这样的
std::mutex f1m, f2m, f3m;
using MuxGuard = std::lock_guard<std::mutex>;

{
	MuxGuard g(f1m);
	auto res = f1(0);
}

{
	MuxGuard g(f2m);
	auto res = f2(NULL);
}

{
	MuxGuard g(f3m);
	auto res = f3(nullptr);
}
```
代码过于冗余, 我们使用模板来优化
```cpp
int f1(std::shared_ptr<Widget> p);
double f2(std::unique_ptr<Widget> p);
bool f3(Widget *p);

using MuxGuard = std::lock_guard<std::mutex>;

template<typename FuncType, typename MuxType, typename PtrType>
decltype(auto) lockAndCall(FuncType func, MuxType &mux, PtrType ptr) {
	MuxGuard g(mux);
	return func(ptr);
}

// 调用
auto res1 = lockAndCall(f1, f1m, 0);	// 出错
auto res2 = lockAndCall(f2, f2m, NULL);	// 出错
auto res3 = lockAndCall(f3, f3m, nullptr);	// 正确
```
此时传入0或NULL，模板就不能正常运行，因为模板在进行推导的过程中，PtrType接受的参数是0或NULL时会被解释为int或long long，而不是指针，所以会出现编译错误，而传入nullptr就不会出现这个问题，因为nullptr是一个指针，所以模板可以正常推导

总结：
1. nullptr是一个指针，可以隐式转换到所有的裸指针类型
2. 相对于0或NULL，优先选用nullptr
3. 避免在整数和指针类别的重载