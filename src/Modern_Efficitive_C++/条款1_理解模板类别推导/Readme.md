## 现代C++模板函数推导规则

对于一个函数模板来讲:

```cpp
template<typename T>
void f(ParamType param);
// 假设调用语句如下
f(expr);
```
T 的类型是由 ParamType 的形式和expr的类型共同决定的.

以下分三类情况讨论:
1. ParamType 是一个指针或者引用, 但不是万能引用
2. ParamType 是一个万能引用
3. ParamType 既不是一个指针也不是一个引用

### 1. ParamType 是一个指针或者引用, 但不是万能引用
在这种情况下, 类别推导会这样运作:
1. 先忽略引用
2. 然后根据expr的类型和ParamType来推导T
```cpp
template<typename T>
void f(T& param);

int x = 27;
const int cx = x;
const int& rx = x;

f(x); // T is int, param's type is int&
f(cx); // T is const int, param's type is const int&
f(rx); // T is const int, param's type is const int&
```

参数为常量引用时也如此，先忽略调const和引用，再根据expr的类型和ParamType来推导T
```cpp
template<typename T>
void f(const T& param);

int x = 27;
const int cx = x;
const int& rx = x;

f(x); // T is int, param's type is const int&
f(cx); // T is int, param's type is const int&
f(rx); // T is int, param's type is const int&
```

### 2. ParamType 是一个万能引用
万能引用是指这样的引用:(万能引用将在条款24中详细讨论)
```cpp
template<typename T>
void f(T&& param);
```

万能引用的类型推导规则:
1. 如果expr是一个左值, 那么T和ParamType都会被推导为左值引用
2. 如果expr是一个右值, 那么T被推导为右值的类型, ParamType都会被推导为右值引用
3. 万能引用会保留expr的const和volatile属性
```cpp
template<typename T>
void f(T&& param);

int x = 27;
const int cx = x;
const int& rx = x;

f(x); // T is int&, param's type is int&
f(cx); // T is const int&, param's type is const int&
f(rx); // T is const int&, param's type is const int&
// 以上三个调用都是左值,和情况1一样
// 如果expr是一个右值, ParamType都会被推导为右值引用
f(27); // T is int, param's type is int&&
```

### 3. ParamType 既不是一个指针也不是一个引用
#### 3.1. 在这种情况下, 我们面对的就是所谓的值传递了, 值传递意味着无论传入的是什么, param都是它的一个副本，即全新的对象
推导规则:
1. 如果expr的类型是引用, 则忽略其引用部分
2. 去掉引用后, 若expr是一个const, 也同样忽略。
```cpp
template<typename T>
void f(T param);

int x = 27;
const int cx = x;
const int& rx = x;

f(x); // T is int, param's type is also int
f(cx); // T is int, param's type is also int
f(rx); // T is int, param's type is also int

```

#### 3.2. 如果参数是指针且是一个底层const, expr的底层const会被保留

底层const含义: 一个指针指向的对象是const, 但是指针本身不是const
顶层const含义: 一个指针本身是const, 但是指针指向的对象不是const
```cpp
template<typename T>
void f(T param);

const char* const ptr = "Fun with pointers";	// ptr is a const pointer to const char
f(ptr); // T is const char*, param's type is const char*
// 顶层const被忽略, 底层const保留
```

#### 3.3. 如果参数是数组时, T会被推导为指向数组首元素的指针, 而不是数组本身
```cpp
template<typename T>
void f(T param);

char name[] = "J. P. Briggs";
f(name); // T is char*, param's type is char*
```

但是实际上数组型别和指针并不完全相同，数组型别包含有对应的数组大小的信息，如果我们希望参数仍然是一个数组型别而不是指针，可以使用引用传值
```cpp
template<typename T>
void f(T& param);

char name[] = "J. P. Briggs";
f(name); // T is char[13], param's type is char (&) [13]
```

很有意思的我们可以利用这个数组引用这个特性创造出一个模板，可以在编译期就知道传入的数组的大小
```cpp
template<typename T, std::size_t N>
constexpr std::size_t arraySize(T (&)[N]) noexcept {
	return N;
}
```

#### 3.4. 如果参数是一个函数, T会被推导为函数指针，我们可以把它和数组参数作为类比
```cpp
template<typename T>
void f1(T param);

template<typename T>
void f2(T& param);

void someFunc(int, double);

f1(someFunc); //param's type is void(*)(int, double)
f2(someFunc); //param's type is void(&)(int, double)

```

总结:
1. 推导结果由expr和ParamType的共同决定
2. 对于万能引用, 左值会被推导为左值引用，其他情况保持原有信息
3. 按值传递的参数会忽略引用, 忽略顶层const, 保留底层const
4. 数组和函数类别的实参会被推导为指针和函数指针, 但是我们可以使用引用传值来保留数组和函数的类别