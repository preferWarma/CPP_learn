#include "threadPool.h"
#include <iostream>

using lyf::ThreadPool;

int main() {
    ThreadPool pool(4);
    auto res1 = pool.enqueue([](int a, int b) {
        // 随机等待1-5秒
        sleep(rand() % 5 + 1);
        std::cout << "a + b = " << a + b << std::endl;
        return a + b;
        }, 1, 2);

    auto res2 = pool.enqueue([](int a, int b) {
        // 随机等待1-5秒
        sleep(rand() % 5 + 1);
        std::cout << "a * b = " << a * b << std::endl;
        return a * b;
        }, 3, 4);

    std::cout << "res1.get() = " << res1.get() << std::endl;
    std::cout << "res2.get() = " << res2.get() << std::endl;

    auto res3 = pool.enqueue([]() {
        // 随机等待1-5秒
        sleep(rand() % 5 + 1);
        std::cout << "hello" << std::endl;
        });

    auto res4 = pool.enqueue([]() {
        // 随机等待1-5秒
        sleep(rand() % 5 + 1);
        std::cout << "world" << std::endl;
        });

    res3.get();
    res4.get();

    return 0;
}