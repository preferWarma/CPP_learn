## 【造轮子】C++实现python中的type函数，并且保留cvr属性

当我们想要查看C++中变量类型的时候，我们可以使用typeid关键字，typeid的返回值是typeInfo类，该类有一个name成员函数可以返回变量类型，但是该方法只能查看变量的类型，而不能查看变量的cvr属性，比如：

```cpp
int a = 1;
const int b = 2;
double c = 3.0;
float d = 4.0f;
cout << typeid(a).name() << endl; // i
cout << typeid(b).name() << endl; // i
cout << typeid(c).name() << endl; // d
cout << typeid(d).name() << endl; // f
```
i表示int，d表示double，f表示float，typeInfo的成员函数返回的是变量的缩写，我们可以使用abi命名空间中的__cxa_demangle函数来返回全名

```cpp
#include <cxxabi.h>
#define getType(expr) abi::__cxa_demangle(typeid(expr).name(), nullptr, nullptr, nullptr)
cout << getType(a) << endl; // int
cout << getType(b) << endl; // int
cout << getType(c) << endl; // double
cout << getType(d) << endl; // float
```

如上可知，虽然我们得到了变量的类型全名，但是损失了cvr属性，即const和volatile属性和引用属性。已知，使用decltype推导变量类型和使用类模板参数的的时候，是可以保留cvr属性的，所以我们考虑使用采用模板参数而不是函数参数的方式获取变量类型
```cpp
template<typename Helper>
	struct cvr_saver {};	// 用于保存变量的const/volatile/reference属性

template<typename T>
class type_class {
public:
	// 获取变量类型(依赖于typeid关键字)
	static std::string get() {
		return std::string{abi::__cxa_demangle(typeid(cvr_saver<T>).name(), nullptr, nullptr, nullptr)};	// 包含cuv_saver结构体的全名
		
	}
};
```

我们可以测试一下
```cpp
int a = 1;
const ca = 1;
int& ra = 1;
cout << type_class<decltype(a)>::get() << endl; 
cout << type_class<decltype(ca)>::get() << endl;
cout << type_class<decltype(ra)>::get() << endl;
```

得到的结果如下:
```cpp
cvr_saver<int>
cvr_saver<int const>
cvr_saver<int&>
```

此时我们以及完成了最大的难题，接下来对这个结果进行字符串切片处理即可
```cpp
namespace lyf {

	template<typename Helper>
	struct cvr_saver {};	// 用于保存变量的const/volatile/reference属性

	/* 采用模板参数而不是函数参数的方式获取变量类型
	获取param的类型的调用格式为lyf::type_class<decltype(param)>::get() */
	template<typename T>
	class type_class {
	public:
		// 获取变量类型(依赖于typeid关键字)
		static std::string get() {
			std::string all_realName = std::string{abi::__cxa_demangle(typeid(cvr_saver<T>).name(), nullptr, nullptr, nullptr)};	// 包含cuv_saver结构体的全名
			int pos1 = all_realName.find_first_of('<') + 1;	// 第一个'<'后的位置
			int pos2 = all_realName.find_last_of('>');	// 最后一个'>'的位置
			std::string realName = all_realName.substr(pos1, pos2 - pos1);	// 去掉干扰信息
			return realName;
		}
	};
}
```

测试一下
```cpp
int a = 1;
const ca = 1;
int& ra = 1;
cout << lyf::type_class<decltype(a)>::get() << endl;	// int
cout << lyf::type_class<decltype(ca)>::get() << endl;	// int const
cout << lyf::type_class<decltype(ra)>::get() << endl;	// int&
```

结果符合我们的预期，这样我们就可以获取变量的类型了，至此我们完成了boost库中的type_id_with_cvr函数。或许你认为这样调用起来比较麻烦, 如果能像python中的type函数一样调用就好了，那么我们可以添加一个宏来实现
```cpp
#define Get_Type(x) lyf::type_class<decltype(x)>::get()	// 用于获取变量类型的快捷调用宏

int a = 1;
const ca = 1;
int& ra = 1;
cout << Get_Type(a) << endl;	// int
cout << Get_Type(ca) << endl;	// int const
cout << Get_Type(ra) << endl;	// int&
```
这样使用起来就非常方便了，至此我们已经完成了我们的全部需求了。