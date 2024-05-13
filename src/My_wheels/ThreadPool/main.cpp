#include "threadPool.h"
#include <iostream>

using lyf::ThreadPool;

int main() {
    ThreadPool pool(4);
    auto res = pool.enqueue([](int a, int b) {
        // 随机等待1-5秒
        sleep(rand() % 5 + 1);
        std::cout << "a + b = " << a + b << std::endl;
        return a + b;
        }, 1, 2);

    auto res1 = pool.enqueue([](int a, int b) {
        // 随机等待1-5秒
        sleep(rand() % 5 + 1);
        std::cout << "a * b = " << a * b << std::endl;
        return a * b;
        }, 3, 4);

    std::cout << "res.get() = " << res.get() << std::endl;
    std::cout << "res1.get() = " << res1.get() << std::endl;

    return 0;
}