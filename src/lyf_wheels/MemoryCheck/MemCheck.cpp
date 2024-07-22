#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstddef>
#include <new>
#include <unordered_map>

using std::size_t;
using std::cout, std::endl;
using std::unordered_map;

#undef new  // 取消new宏定义

bool traceFlag = true;
bool activeFlag = false;

namespace {
    struct Info {
        size_t size;
        const char* file;
        long line;
    };

    const size_t MAXPTRS = 10'0000u;  // 最大指针数
    unordered_map<void*, Info> memMap;    // 用于存储分配的指针信息

    struct Sentinel {   // 用于析构时检查内存泄漏
        ~Sentinel() {
            if (!memMap.empty()) {
                cout << "Leaked memory at: " << endl;
                for (const auto& [ptr, info] : memMap) {
                    cout << "\t" << ptr << " with size: " << info.size
                        << " (file: " << info.file << ", line: " << info.line << ")\n";
                }
            }
            else {
                cout << "No user memory leaks!" << endl;
            }
        }
    };

    Sentinel sentinel;
}   // namespace

// 开始重载new和delete
void* operator new(std::size_t size, const char* file, long line) {
    void* ptr = std::malloc(size);
    if (ptr == nullptr) {
        throw std::bad_alloc();
    }
    if (activeFlag) {
        if (memMap.size() == MAXPTRS) {
            cout << "Memory limit exceeded!(increase MAXPTRS)" << endl;
            exit(1);
        }
        memMap[ptr] = { size, file, line }; // 这里在memMap内部会调用一次全局的new(因为我们已经#undef new了), 所以不会出现递归调用
    }
    if (traceFlag) {
        cout << "Allocated " << size << " bytes at adress: " << ptr << " (file: " << file << ", line: " << line << ")" << endl;
    }
    return ptr;
}

void* operator new[](std::size_t size, const char* file, long line) {
    return operator new(size, file, line);
}

bool memMap_erase_flag = false; // 针对memMap.erase(ptr)时也会调用一次delete, 所以这里设置一个标志位, 防止再次调用我们重载的delete
void operator delete(void* ptr) noexcept {
    if (memMap.find(ptr) != memMap.end()) {
        if (traceFlag) {
            cout << "Deallocated memory at adress: " << ptr << endl;
        }
        std::free(ptr);
        memMap_erase_flag = true;
        memMap.erase(ptr);  // 这里内部也调用了delete来删除map中指向ptr的那块儿内存, 会再次调用这个函数, 但是此时里面的指针不在map中
    }
    else if (activeFlag) {
        if (memMap_erase_flag) {    // 如果此时是由memMap.erase(ptr)调用的delete, 则不再次调用我们重载的delete, 直接free掉
            memMap_erase_flag = false;
            std::free(ptr);
        }
        else {
            cout << "Trying to delete unknown ptr: " << ptr << endl;
        }
    }
}

void operator delete[](void* ptr) noexcept {
    operator delete(ptr);
}

void operator delete(void* ptr, std::size_t size) noexcept {
    operator delete(ptr);
}

void operator delete[](void* ptr, std::size_t size) noexcept {
    operator delete(ptr);
}