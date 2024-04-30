#include "lyf.h"

using namespace lyf;
using namespace std;

// 通用单例模式测试类
class Foo : public Singleton<Foo> {
public:
    void print() {
        cout << this->str << endl;
    }
private:
    string str = "Hello, world!";
};

int main() {
    string str = "hello world!";

    // 字符串分割
    auto res = split(str, ' ');
    print_container(res, "\n"); // 容器快捷打印

    // 正则表达式匹配
    string pattern = R"(\d{3,4}-\d{7,8})";
    string text = "电话号码: 010-12345678, 021-87654321";
    auto regex_res = regex_match(text, pattern);
    print_container(regex_res, "\n");

    // 字符串替换
    auto res2 = replace_first(str, "world", "lyf");
    auto res3 = replace_last(str, "world", "USTC");
    auto res4 = replace_all(str, "world", "WHU");

    // 参数打印
    lyf::printDelim = "\n"; // 设置分隔符
    lyf::delimIsPersist = true; // 设置分隔符持久化
    print_args(res2, res3, res4);

    // beginWith和endWith
    cout << begin_with(str, "hello") << endl;
    cout << begin_with(str, "world") << endl;
    cout << end_with(str, "world") << endl;
    cout << end_with(str, "world!") << endl;

    // 通用单例模式
    Singleton<Foo>::GetInstance().print();  // 显式表达
    Foo::GetInstance().printAdress();   // 简单表达
    Singleton<Foo>::GetInstance().printAdress();

    // 通用max和min, 类型推导宏typeof
    cout << typeof(max(1, 1.5f)) << endl;
    cout << typeof(min(1, 1.5)) << endl;
    cout << typeof(Singleton<Foo>::GetInstance()) << endl;

    return 0;
}