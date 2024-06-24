#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstddef>
#include <new>

using std::size_t;
using std::cout, std::endl;

#undef new  // 取消new宏定义

bool traceFlag = true;
bool activeFlag = false;

namespace {
    struct Info {
        void* ptr;
        const char* file;
        long line;
    };

    const size_t MAXPTRS = 10000u;  // 最大指针数
    Info memMap[MAXPTRS];
    size_t nptrs = 0u;  // 当前指针数

    // 查找指针
    int findPtr(void* ptr) {
        for (size_t i = 0; i < nptrs; ++i) {
            if (memMap[i].ptr == ptr) return i;
        }
        return -1;
    }

    // 删除指针
    void delPtr(void* ptr) {
        int pos = findPtr(ptr);
        assert(pos >= 0);
        for (size_t i = pos; i < nptrs - 1; ++i) {
            memMap[i] = memMap[i + 1];
        }
        --nptrs;
    }

    struct Sentinel {   // 用于析构时检查内存泄漏
        ~Sentinel() {
            if (nptrs > 0) {
                cout << "Leaked memory at: " << endl;
                for (size_t i = 0; i < nptrs; ++i) {
                    cout << "\t" << memMap[i].ptr << " (file: " << memMap[i].file << ", line: " << memMap[i].line << ")\n";
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
    if (activeFlag) {
        if (nptrs == MAXPTRS) {
            cout << "Memory limit exceeded!(increase MAXPTRS)" << endl;
            exit(1);
        }
        memMap[nptrs++] = { ptr, file, line };
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
    if (findPtr(ptr) >= 0) {
        std::free(ptr);
        assert(nptrs > 0);
        delPtr(ptr);
        if (traceFlag) {
            cout << "Deallocated memory at adress: " << ptr << endl;
        }
    }
    else if (!ptr && activeFlag) {
        cout << "Trying to delete unknown ptr: " << ptr << endl;
    }
}

void operator delete[](void* ptr) noexcept {
    operator delete(ptr);
}

void operator delete(void* ptr, std::size_t size) noexcept
{
    operator delete(ptr);
}

void operator delete[](void* ptr, std::size_t size) noexcept
{
    operator delete(ptr);
}