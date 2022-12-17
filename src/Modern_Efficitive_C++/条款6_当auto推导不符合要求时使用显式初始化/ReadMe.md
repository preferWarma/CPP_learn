## 当auto推导不符合要求时使用带显式类别的初始化

在有的情况下，auto推导结果可能与期望不符合，假设我有一个函数接受一个Widget并返回一个std::vector<bool>，其中每一个bool元素都代表着Widget是否提供一种特定的功能
```cpp
std::vector<bool> getFeatures(const Widget& w);
```

假设第5个位置的意识是Widget是否具有高优先级，那么我可以这样写
```cpp
Widget w;
bool priority = getFeatures(w)[5];
processWidget(w, priority);	// 按照w的优先级处理一些功能
```

在此基础上，我们若使用auto，那么就会出现问题
```cpp
auto features = getFeatures(w)[5];
processWidget(w, features);	// 无法通过编译
```

尽管从概念上来看，std::vector<bool>应该持有的是bool类型的元素，但是实际上它的operator[]的返回值并不是容器的元素的引用，而是一个std::vector<bool>::reference类型的对象，它是一个代理类，之所以是这样的原因是C++中禁止对比特的引用，std::vector<bool>::reference可以做一个向bool类型的隐式转化，但是并非是bool&，这也就是为什么采用bool来声明可以得到正确的结果，而采用auto就会出现问题的原因

因此，你要防止写出这样的代码：
```cpp
auto someVar = "隐形"代理表达式;
```

可以使用带显式类别的初始化来避免这种情况
```cpp
auto someVar = static_cast<"显式类型">("隐形"代理表达式);

上例可以改为：
bool priority = static_cast<bool>(getFeatures(w)[5]);
```

总结：
1. "隐形"的代理表达式可能会导致auto推导出的类型与期望不符合
2. 使用带显式类别的初始化来避免这种情况