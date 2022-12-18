#include <iostream>
#include <vector>

int fun(int a, int b) {
    return a + b;
}

using pf = decltype(fun)*;

int main() {
    std::vector<pf> v;
    v.push_back(fun);
    std::cout << v[0](1, 2);

    int (*p)(int, int) = fun;
    std::cout << p(1, 2);
    return 0;
}