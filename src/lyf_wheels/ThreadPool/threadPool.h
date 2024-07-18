#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <unistd.h>

using std::future;
using std::vector, std::queue;
using std::thread, std::mutex, std::condition_variable;
using std::unique_lock;
using std::function, std::result_of;

namespace lyf {
    class ThreadPool {
    public:
        ThreadPool(size_t thread_count);
        ~ThreadPool();

        template<class F, class... Args>
        auto enqueue(F&& f, Args&&... args) -> future<typename result_of<F(Args...)>::type>;

    private:
        vector<thread> m_workers;   // 工作线程
        queue<function<void()>> m_tasks;   // 任务队列
        mutex m_queueMutex;   // 互斥锁
        condition_variable m_condition;   // 条件变量
        bool m_stop;   // 是否停止
    };

    inline ThreadPool::ThreadPool(size_t thread_count) : m_stop(false) {
        // 设置线程数
        for (size_t i = 0; i < thread_count; ++i) {
            m_workers.emplace_back([this]() {
                while (true) {
                    function<void()> task;  // 存储从任务队列中取出的任务
                    // 临界区
                    {
                        // 加锁
                        unique_lock<mutex> lock{ this->m_queueMutex };
                        // 阻塞线程直到等待条件变量为真(任务队列不为空或者停止标志为真)
                        this->m_condition.wait(lock, [this]() {
                            return this->m_stop || !this->m_tasks.empty();
                            });
                        // 如果停止标志为真且任务队列为空，则退出
                        if (this->m_stop && this->m_tasks.empty()) return;
                        // 取出任务
                        task = std::move(this->m_tasks.front());
                        this->m_tasks.pop();
                    }
                    task();
                }
                });
        }
    }

    inline ThreadPool::~ThreadPool() {
        // 通知所有线程停止
        {
            // 加锁
            unique_lock<mutex> lock{ m_queueMutex };
            m_stop = true;
        }
        // 唤醒所有线程
        m_condition.notify_all();
        // 等待所有线程结束
        for (auto& worker : m_workers) {
            worker.join();
        }
    }

    template<class F, class ...Args>
    auto ThreadPool::enqueue(F&& f, Args&& ...args) -> future<typename result_of<F(Args ...)>::type>
    {
        using returnType = typename result_of<F(Args ...)>::type;

        // 用packaged_task封装一个异步任务, returnType()表示一个无参函数类型, 返回值为returnType
        // 返回的task是一个指向packaged_task的shared智能指针
        auto task = std::make_shared<std::packaged_task<returnType()>>(
            // bind函数将f和args绑定在一起, 使其成为一个无参的可调用对象
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        // 获取任务的future
        auto res = task->get_future();
        {
            // 加锁
            unique_lock<mutex> lock{ m_queueMutex };
            // 如果线程池已经停止，则抛出异常
            if (m_stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            // 将任务放入队列
            m_tasks.emplace([task]() {
                (*task)();  // 执行任务
                });
        }

        // 唤醒线程执行任务
        m_condition.notify_all();
        return res;
    }
}   // namespace lyf

#endif // THREADPOOL_H