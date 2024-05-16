#include "lyf.h"

using namespace lyf;
using namespace lyf::StringTool;
using namespace lyf::PrintTool;
using namespace std;

// 通用单例模式测试类
class Foo : public Singleton<Foo> {
public:
    void print() {
        cout << this->str << endl;
    }
private:
    string str = "Hello, Foo!";
};

// 通用单例模式测试类
class Foo2 : public Singleton<Foo2> {
public:
    void print() {
        cout << this->str << endl;
    }
private:
    string str = "Hello, Foo2!";
};

int main() {
    string str = "hello world!";

    cout << "----------字符串分割------------\n" << endl;

    // 字符串分割
    auto res = split(str, ' ');
    print_container(res, "\n"); // 容器快捷打印(基于迭代器和operator<<重载)

    cout << "--------正则表达式匹配-----------\n" << endl;

    // 正则表达式匹配
    string pattern = R"(\d{3,4}-\d{7,8})";
    string text = "电话号码: 010-12345678, 021-87654321";
    auto regex_res = regex_match(text, pattern);
    print_container(regex_res, "\n");

    cout << "-----字符串替换与参数打印--------\n" << endl;

    // 字符串替换
    auto res2 = replace_first(str, "world", "lyf");
    auto res3 = replace_last(str, "world", "USTC");
    auto res4 = replace_all(str, "world", "WHU");

    // 参数打印
    PrintTool::printDelim = "\n"; // 设置分隔符
    PrintTool::delimIsPersist = true; // 设置分隔符持久化
    print_args(res2, res3, res4);

    cout << "------beginWith和endWith--------\n" << endl;

    // beginWith和endWith
    cout << std::boolalpha << begin_with(str, "hello") << endl;
    cout << std::boolalpha << begin_with(str, "world") << endl;
    cout << std::boolalpha << end_with(str, "world") << endl;
    cout << std::boolalpha << end_with(str, "world!") << endl;

    cout << "\n---------通用单例模式------------\n" << endl;

    // 通用单例模式
    Singleton<Foo>::GetInstance().print();  // 也可以用Foo::GetInstance().print();
    Foo2::GetInstance().print(); // 也可以用Singleton<Foo2>::GetInstance().print();
    // 两次打印地址相同, 说明是同一个对象
    Singleton<Foo>::GetInstance().printAdress();
    Foo::GetInstance().printAdress();
    // 两次打印地址相同, 说明是同一个对象
    Foo2::GetInstance().printAdress();
    Singleton<Foo2>::GetInstance().printAdress();

    cout << "\n--通用多参数max和min和范围比较函数--\n" << endl;

    // 通用多参数max和min和范围比较函数
    cout << max(1, 1.5f, -5.0, 8.8, 'a', 'b') << endl;
    cout << min(1, 1.5f, -5.0, 8.8, 'a', 'b') << endl;

    vector<int> vec = { 1, 2, 3, 4, 5 };
    cout << range_max(vec.begin(), vec.end()) << endl;
    cout << range_min(vec.begin(), vec.end()) << endl;
    cout << range_compare(vec.begin(), vec.end(), [](int a, int b) { return a < b; }) << endl;  // 等价于求最大值

    cout << "\n---------类型推导宏typeof---------\n" << endl;

    // 类型推导宏typeof
    cout << typeof(Singleton<Foo>::GetInstance()) << endl;


    cout << "\n---------------lyf-----------------\n" << endl;

    return 0;
}