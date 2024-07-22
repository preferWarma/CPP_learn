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
                    cout << "\t" << ptr << " (file: " << info.file << ", line: " << info.line << ")\n";
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
        memMap[ptr] = { file, line };
    }
    if (traceFlag) {
        cout << "Allocated " << size << " bytes at adress: " << ptr << " (file: " << file << ", line: " << line << ")" << endl;
    }
    return ptr;
}

void* operator new[](std::size_t size, const char* file, long line) {
    return operator new(size, file, line);
}

void operator delete(void* ptr) noexcept {
    if (memMap.find(ptr) != memMap.end()) {
        if (traceFlag) {
            cout << "Deallocated memory at adress: " << ptr << endl;
        }
        std::free(ptr);
        memMap.erase(ptr);
    }
    else if (!ptr && activeFlag) {
        cout << "Trying to delete unknown ptr: " << ptr << endl;
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