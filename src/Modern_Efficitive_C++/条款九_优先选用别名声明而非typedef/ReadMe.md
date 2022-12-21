## 优先选用别名声明，而非typedef
有时候我们使用std的容器的，会出现非常复杂的类型名称，比如std::unique_ptr<std::unordered_map<std::string, std::string>>，如果每次都一遍遍的写会显得非常冗余，在C++11以前我们可以使用typedef来解决这个问题
```cpp
typedef std::unique_ptr<std::unordered_map<std::string, std::string>> UPtrMapSS;
```
我们用UptrMapSS来作为这个变量类型，这样写没问题，但是C++11以后，我们可以使用using来代替typedef，这样写起来更加简洁而且可读性更强
```cpp
using UPtrMapSS = std::unique_ptr<std::unordered_map<std::string, std::string>>;
```

或许你觉得两者之间似乎没什么差别，但是当涉及到函数指针的别名的时候，using就显得更加优雅了
```cpp
typedef void (*FuncPtr)(int, int);
using FuncPtr = void (*)(int, int);
```
当然，using也可以用来定义模板别名
```cpp
template<typename T>
using MyAllocList = std::list<T, MyAlloc<T>>;

// 客户代码
MyAllocList<int> lst;
```
如果在模板中使用typedef就显得十分麻烦
```cpp
template<typename T>
struct MyAllocList {
	typedef std::list<T, MyAlloc<T>> type;
};
// 客户代码
MyAllocList<int>::type lst;
```
还有更坏的情况，在模板内创建一个链表，然后让它容纳的元素类型是模板参数时，那你还需要给typedef的名字加一个typename的前缀
```cpp
template<typename T>
class Widget {
private:
	typename MyAllocList<T>::type data;
};
```

如果是使用using来进行别名声明的话就不需要这样的麻烦了，使用起来也更加符合直觉
```cpp
template<typename T>
class Widget {
private:
	MyAllocList<T> data;
};
```
如果你接触过C++元编程，那么肯定见过这样的代码
```cpp
std::remove_const<T>::type
```
在C++14后，std统一对这些进行了别名声明，用remove_const_t来代替std::remove_const<T>::type，这样写起来更加简洁，更加直觉，我们可以动手实现一下
```cpp
template<typename T>
using remove_const_t = typename std::remove_const<T>::type;
```

总结：
1. typedef不支持模板化，但using支持
2. 使用using来声明别名的模板可以避免让人写::type的后缀，而且在模板内，对于内嵌的typedef的引用，需要加上typename前缀，而using不需要