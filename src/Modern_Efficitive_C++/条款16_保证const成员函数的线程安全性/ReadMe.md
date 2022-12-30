## 保证const成员函数的线程安全性

在数学领域中，我们经常使用一个类表示多项式，在这样的类当中，通常会提供一个函数能够计算多项式的根。很自然的我们可以知道，这个函数不会造成多项式的值的改动，可以声明为const函数。
```cpp
class Polynomial {
public:
	using RootType = std::vector<double>;	// 根的类型

	RootType roots() const {	
		if (!rootsAreValid) {
			rootsAreValid = true;
			// rootsVals = ...;	// 计算根
		}
		return rootsVals;
	}

private:
	mutable bool rootsAreValid{ false };	// 缓存根的有效性
	mutable RootType rootsVals;	// 根的值
};
```

从概念上来看，roots不会操作Polynomial对象，然而作为缓存活动的组成部分，它可能需要修改rootsVals和rootsAreValid的值。这是mutable的经典用法，也是它为何被加到数据成员的声明中。

设想有两个线程调用同一个Polynomial对象的roots函数
```cpp
Polynamial p;

/* -----线程1 ------ */
auto r1 = p.roots();

/* -----线程2 ------ */
auto r2 = p.roots();
```

上述用户代码完全合理，roots是一个const成员函数，这意味着它代表的是一个读操作，多个线程在没有同步的条件下是安全的，但是在本例中却不安全。在roots内部，这些线程可能会修改数据成员rootsAreValid和rootsVals [因为mutable变量每次都是从内存中重新取值]，所以这段代码可能会有不同的多个线程在没有同步的情况下读写同一块内存，造成数据竞争。

为了解决这个问题，我们需要保证const成员函数的线程安全性，在本例中可以引入一个mutex互斥量，保证roots函数的互斥访问。
```cpp
class Polynomial {
public:
	using RootType = std::vector<double>;	// 根的类型

	RootType roots() const {	
		std::lock_guard<std::mutex> g(m);	// 保证互斥访问
		if (!rootsAreValid) {
			rootsAreValid = true;
			// rootsVals = ...;	// 计算根
		}
		return rootsVals;
	}

private:
	mutable std::mutex m;	// 互斥量
	mutable bool rootsAreValid{ false };	// 缓存根的有效性
	mutable RootType rootsVals;	// 根的值
};
```
这里的mutex之所以声明为mutable，是因为加锁和解锁都不是const成员函数所为，如果没有这样的声明，在roots函数内，m会被当成一个const对象来处理了。

就一些特定的情况而言，引入互斥量有些大材小用了，如果只是要计算一个成员函数被调用的次数，可以使用std::atomic的计数器，是比较低成本的实现途径。
```cpp
class Point {
public:
	double distanceFromOrigin() const noexcept {
		++callCount;	// 计数器
		return std::sqrt(x * x + y * y);
	}
private:
	mutable std::atomic<unsigned> callCount{ 0 };	// 计数器
	double x, y;

};
```
这里提一下：对于单个要求同步的变量或内存区域，使用std::atomic就足够了，如果有两个或者更多的变量或内存区域需要作为一个整体进行操作的时候，就要使用互斥量了。

总结：
1. 保证const成员函数的线程安全性，除非可以确保它不会用在并发环境中。
2. 使用std::atomic类别的变量可以提供比使用互斥量更好的性能，但是前者仅适用对单个变量或内存区域的操作