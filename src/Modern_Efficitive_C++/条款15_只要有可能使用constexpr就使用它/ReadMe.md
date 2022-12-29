## 只要有可能使用constexpr就使用它

当constexpr作用于对象时，它就是一个加强版的const。但是当它作用于一个函数时，有着相当不同的意义。

表面上来讲，constexpr表示的是这样的值：它不仅仅是const，而且在编译阶段就可以被推导出来。但是作用于函数的时候，这样的描述不太准确，关于constexpr函数结果，你既不能断定它是const，也不能假定其值在编译阶段就是已知的。

我们首先从constexpr对象讲起。这些对象的值具备const属性，不可修改，且在编译期间就能得到其值，它们拥有编译器优化的特权，比如，可能被放置在只读内存里。在更广泛的应用场景里，在编译期已知的常量整型值可以用在C++的整型常量表达式的语境中，比如数组的尺寸，整型模板std::array的实参中，枚举的值，对齐规格等等。
```cpp
int sz;	// 非constexpr变量
constexpr auto arraySize = sz;	// 编译错误，sz的值在编译期未知
std::array<int, sz> data1;	// 编译错误，sz的值在编译期未知
constexpr auto arraySize = 10;	// 正确，10是一个编译期常量
std::array<int, arraySize> data2;	// 正确
```

值得注意的是，const对象并不一定由编译期已知的值来初始化
```cpp
int sz;
const auto arraySize = sz;
std::array<int, arraySize> data;	// 错误，arraySize的值在编译期未知
```

总结的说，constexpr对象都是const对象，但是const对象不一定是constexpr对象。

当constexpr对象作用于函数时，函数在调用时若传入的是编译期常量，则返回值为编译期常量，如果传入的是运行期才知道的值，则返回运行期值

关于constexpr正确的理解方式应该是这样的: 
- 当传入参数是编译期常量，则函数返回值在编译期就计算出来，如果传入参数是运行期量，那么该constexpr函数和普通函数无异，这样可以避免写两个函数的麻烦。

设想一个这样一个场景，我们需要一个可以存放3^n个值的空间，其中n的值是在编译期就已知的，而std::pow函数是非constexpr的，我们不能用它来指定std::array的大小，我们可以自己写一个这样的pow函数：
```cpp
constexpr int pow(int base, int exp) noexcept {
	// 快速幂
	if (exp == 0) return 1;
	int result = 1;
	while (exp) {
		if (exp & 1) {	// 奇数
			result *= base;
		}
		base *= base;
		exp >>= 1;
	}
	return result;
}

constexpr auto numConds = 5;
std::array<int, pow(3, numConds)> results;
```

值得注意的是，constexpr是对象或函数接口的一部分。如果一把一个对象或函数声明成了constexpr，后来又觉得不恰当想移出它，这个动作可能会导致非常多的客户代码被拒绝编译(比如向constexpr函数体中添加一条IO语句，通常来讲constexpr函数里不允许有IO语句)。

总结：
1. constexpr对象都具备const属性，其值在编译期就已知
2. constexpr函数在调用时，若传入的是编译期常量，则返回值为编译期常量。
3. 比起非constexpr对象或函数而言，constexpr对象或函数可以用在一个作用域更广的语境中