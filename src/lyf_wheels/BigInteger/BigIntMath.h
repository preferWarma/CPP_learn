#ifndef BIGINTMATH_H_
#define BIGINTMATH_H_

#include <future>
#include "BigInteger.h"

namespace lyf {
    namespace BigIntMath {
        BigInteger partial_factorial(size_t start, size_t end) {
            BigInteger res(1);
            for (int i = start; i <= end; ++i) {
                res *= i;
            }
            return res;
        }

        BigInteger factorial(size_t n, size_t thread_cnt = 1) {
            if (n < 1000) return partial_factorial(1, n);
            // 计算每个线程的任务量
            size_t task_size = n / thread_cnt;
            // 保存每个线程的返回值
            vector<std::future<BigInteger>> futures;
            for (size_t i = 0; i < thread_cnt; ++i) {
                size_t start = i * task_size + 1;
                size_t end = (i == thread_cnt - 1) ? n : (i + 1) * task_size;
                futures.emplace_back(std::async(std::launch::async, partial_factorial, start, end));
            }
            // 等待所有线程结束, 并将结果合并
            BigInteger res(1);
            for (auto& f : futures) {
                res *= f.get();
            }
            return res;
        }
    }   // namespace BigIntMath
}   // namespace lyf

#endif /* !BIGINTMATH_H_ */
