#include <iostream>
#include <windows.h>
#include <string_view>
#include <fstream>
#include <vector>
#include <memory>

#include "MemCheck.h" // 用于内存泄漏检测, 必须放在所有头文件的最后

class Foo {
public:
    Foo(const char* s) {
        this->s = new char[strlen(s) + 1];
        strcpy(this->s, s);
    }
    ~Foo() {
        delete[] s;
    }
private:
    char* s;
};

int main() {
    // TRACE_OFF(); // 关闭内存泄漏检测追踪报告
    MEM_ON();

    int* p = new int;
    int* q = new int[3];

    delete p;
    delete[] q;

    // 会有内存泄漏
    std::vector<int>* v = new std::vector<int>{};
    v->push_back(1);

    // 改用智能指针则不会有内存泄漏
    std::unique_ptr<std::vector<int>> up = std::make_unique<std::vector<int>>();
    up->push_back(1);

    auto f = new Foo("this is a test string!");
    delete f;

    MEM_OFF();

    std::puts("---------------Memory check over!------------");

    return 0;
}