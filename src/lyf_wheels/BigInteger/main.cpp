#include <iostream>
#include <cassert>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>

#include "BigInteger.h"
#include "../lyf.h"
#include "../stopwatch.h"
#include "../MemoryCheck/MemCheck.h"

using namespace lyf;
using namespace std::chrono;

int main() {
    TRACE_OFF();
    MEM_ON();
    stopwatch sw(stopwatch::TimeType::ms);
    sw.start();

    m_print(std::to_string(UINT64_MAX));

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

    MEM_OFF();

    sw.stop();
    cout << "Duration Time: " << sw.duration() << " ms" << endl;
    return 0;
}