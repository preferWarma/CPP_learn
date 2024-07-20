#include <iostream>
#include <cassert>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>

#include "BigInteger.h"
#include "BigIntMath.h"
#include "../lyf.h"
#include "../stopwatch.h"
#include "../MemoryCheck/MemCheck.h"

using namespace lyf;
using namespace std::chrono;

#define test(x) test_##x()

void test_1() {
    BigInteger a(UINT64_MAX);
    BigInteger b(std::to_string(UINT64_MAX));
    BigInteger c(INT64_MAX);
    BigInteger d(INT64_MIN);
    m_print(a);
    m_print(b);
    m_print(c);
    m_print(d);
    m_print((a == b));
    m_print((a - b));
    m_print((a == 18446744073709551615ULL));
    m_print((a > c));
    m_print((c + d));
    m_print((a == (c - d)));
    m_print((a - c));
    m_print((a + c));
}

void test_2() {
    constexpr int slen = 1e5;
    string as;  // as设置为一个99999...9999(slen位)的字符串
    for (int i = 0; i < slen; ++i) {
        as.push_back('9');
    }
    BigInteger a(as);
    m_print(a);
    BigInteger b = a + 1;
    m_print(b);

    string bs = "1";
    for (int i = 0; i < slen; ++i) {
        bs.push_back('0');
    }

    assert(b == BigInteger(bs));

    m_print(a.getRawVector().size());
    m_print(b.getRawVector().size());
    PrintTool::print_container(a.getRawVector());
    PrintTool::print_container(b.getRawVector());
}

void test_3() {
    m_print(UINT64_MAX);
    auto data = BigInteger(UINT64_MAX).getRawVector();
    PrintTool::print_container(data);
}

void test_4() {
    BigInteger a(UINT64_MAX);
    BigInteger b(UINT64_MAX);
    m_print(a);
    m_print(b);
    m_print(a + b);
    m_print(a * 2);
    assert(((a * 2) == (a + b)));
    assert((a * b == a * UINT64_MAX));
    m_print(a * b);
}

void test_5() {
    stopwatch sw(stopwatch::TimeType::ms);
    auto func = [&](int n, int thread_n) {
        sw.start();
        auto res = BigIntMath::factorial(n, thread_n);
        sw.stop();
        cout << "计算" << n << "!(" << thread_n << "线程)耗时: " << sw.duration() << " ms" << endl;
        };

    func(1000, 1);
    func(5000, 1);
    func(5000, 2);
    func(5000, 4);
    func(10000, 1);
    func(10000, 4);
}

int main() {
    TRACE_OFF();
    MEM_ON();
    stopwatch sw(stopwatch::TimeType::ms);
    sw.start();

    test(5);

    MEM_OFF();
    sw.stop();
    cout << "Total Duration Time: " << sw.duration() << " ms" << endl;
    return 0;
}