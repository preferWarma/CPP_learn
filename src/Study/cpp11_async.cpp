#include <future>
#include <iostream>
#include <unistd.h>
#include <chrono>

using namespace std::chrono_literals;   // C++14中引入的时间单位，秒、毫秒、微秒、纳秒等

using std::future;
using std::cout, std::endl;
using std::future_status;


int main() {
    future<int> res = std::async([]() {
        sleep(5);   // 等待5秒
        return 8;
        });
    cout << "Waiting..." << endl;
    auto status = res.wait_for(3s);  // 最多等待3秒
    if (status == future_status::ready) {
        cout << "Result is " << res.get() << endl;
    }
    else if (status == future_status::timeout) {
        cout << "Timeout" << endl;
    }
    else if (status == future_status::deferred) {
        cout << "Deferred" << endl;
    }

    cout << "====================\n";

    auto res1 = std::async([]() {
        sleep(2);   // 等待2秒
        return 8;
        });
    cout << "Waiting..." << endl;
    auto status1 = res1.wait_for(3s);   // 最多等待3秒
    if (status1 == future_status::ready) {
        cout << "Result is " << res.get() << endl;
    }
    else if (status1 == future_status::timeout) {
        cout << "Timeout" << endl;
    }
    else if (status1 == future_status::deferred) {
        cout << "Deferred" << endl;
    }

    return 0;
}