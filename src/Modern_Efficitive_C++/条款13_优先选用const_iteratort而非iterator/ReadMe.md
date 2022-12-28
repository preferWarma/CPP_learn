## 优先选用const_iterator而非iterator

const_iterator是STL中相当于const的指针的等价物，它们指向不可被修改的值。只要有可能就应该使用const的标准时间表明，任何时候只要你需要一个迭代器而其指向的内容没有必要修改，你就应该使用const_iterator。


C++11以前，const_iterator没法直接完成到iterator的类型转换，在C++11以后，const_iterator的处境得到了改善，容器的cbegin函数和cend函数都返回的是const_iterator，甚至对于非const的容器也是如此，并且STL成员函数若要取用指定位置的迭代器（例如用于插入或删除），它们也要求使用const_iterator类别。
```cpp
std::vector<int> values;
auto it = std::find(values.cbegin(), values.cend(), 1983);
values.insert(it, 1998);
```

只有一种情况下，C++11对const_iterator的支持不够充分，当你想撰写最通用化的库代码的时候，某些容器，或类似容器的数据结构会以非成员函数的方法提供begin和end等。也是某些仅以自由函数形式提供接口的第三方库的情况，举例来讲
```cpp
template <typename C, typename V>
void findAndInsert( C& container,	// 容器中查找targetVal 
					const V& targetVal,	// 查找目标第一次出现
					const V& insertVal)	// 插入insertVal
{
	using std::cbegin;
	using std::cend;
	auto it = std::find(cbegin(container), cend(container), targetVal);
	container.insert(it, insertVal);
}
```
上述代码可以在C++14及以后正常运行，但是C++11并不支持，C++11仅仅添加了非成员函数版本的begin和end，而没有提供cbegin或cend等，当然你也可以自己造一个cbegin的轮子
```cpp
template <typename C>
auto cbegin(const C& container) -> decltype(std::begin(container))
{
	return std::begin(container);
}
```
总结：
1. 优先选用const_iterator而非iterator
2. 在最通用的代码中，优先选用非成员函数版本的begin和end和rebegin和rend等，而非其成员函数版本