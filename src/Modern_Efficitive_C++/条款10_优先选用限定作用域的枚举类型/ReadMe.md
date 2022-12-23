## 优先选用限定作用域的枚举类型，而非不限作用域的枚举类型

一个通用的规则，如果在一对大括号里声明一个变量，那么该变量的可见性就限定于这对大括号内，但这个规则不适用于C++98枚举类型定义的枚举量
```cpp
enum Color {red, green, blue}; // red，green，blue的可见性和Color一样
auto red = false;	// 错误，red已经被定义为枚举量
```

在C++11后，我们可以限定枚举的作用范围
```cpp
enum class Color {red, green, blue}; // red，green，blue的可见性限定在Color内
Color r1 = Color::red;	// 正确，red是Color的枚举量
auto r2 = red;	// 错误，red未定义
```
限定作用域的枚举类型可以降低名字空间污染，同时也可以避免枚举量的隐式转换。不限定范围的枚举类型中的枚举量是可以隐式转换到int类型的，而限定范围的枚举类型中的枚举量则不可以隐式转换到int类型。
```cpp
// 可能会出现以下的古怪语义
enum Color {red, green, blue};	// 不限定作用域的枚举类型
Color c1 = red;
if (c1 < 14.5) {
	// ...
}
```
上述代码是没有语法错误的,但是其质量属实堪忧，限定作用域的枚举类型可以避免这种情况的发生
```cpp
enum class Color {red, green, blue};	// 限定作用域的枚举类型
Color c1 = Color::red;
if (c1 < 14.5) {	// 出错，不能将Color类型和double类型进行比较
	// ...
}
```

在C++11中，对于不限定作用域的枚举类型，编译器会选择一个整数类别作为其底层类型，如enum Color {red, green, blue};，编译器会选择char来作为其底层，如果有些枚举范围非常大,比如
```cpp
enum Status { 	good = 0,
				failed = 1,
				imcomplete = 100,
				corrupt = 200,
				indeterminate = 0x7FFFFFFF};
```
这里的枚举范围是从0到0x7FFFFFFF， 编译器会自动选择足够表示枚举量取值的最小字节数的底层类型,但是这样依赖编译性导致其对前置声明的能力会造成一定的弊端，而限定作用域的枚举类型的其底层类型默认是int

总结
1. 限定作用域的枚举类型可以降低名字空间污染
2. 限定作用域的枚举类型可以避免枚举量的隐式转换
3. 限定作用域的枚举类别的默认底层类型是int，而不限定作用域的枚举类型没有默认底层类型，编译器会选择一个符合要求的整数类别作为其底层类型