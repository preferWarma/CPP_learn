/*
以vector为例, 简述std::move的作用
*/

#include <iostream>
#include <vector>
using namespace std;

struct Test {};

int main() {
    vector<Test> v1;
    v1.emplace_back(Test{});
    cout << addressof(v1[0]) << endl;

    vector<Test> v2{ v1 };
    cout << addressof(v2[0]) << endl;   // 与v1[0]地址不同, 说明拷贝构造创造了新的对象

    vector<Test> v3{ std::move(v1) };
    cout << addressof(v3[0]) << endl;   // 与v1[0]地址相同, 说明移动构造只转移了所有权(指针), 没有创造新的对象
    cout << addressof(v1[0]) << endl;   // 0x0, v1[0]已经被移动构造函数置为nullptr
    cout << addressof(v2[0]) << endl;   // 与原先v2[0]的地址一致

    cout << "v1.size() = " << v1.size() << endl;    // 0, v1的元素所有权已被转移
    cout << "v2.size() = " << v2.size() << endl;    // 1, v2的元素是拷贝构造得到的
    cout << "v3.size() = " << v3.size() << endl;    // 1, v3的元素是移动构造得到的, 即原先v1的元素

    return 0;
}