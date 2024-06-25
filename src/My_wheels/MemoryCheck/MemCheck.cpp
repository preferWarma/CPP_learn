#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstddef>
#include <new>
#include <vector>

using std::size_t;
using std::cout, std::endl;
using std::vector;

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
    vector<Info> memMap;    // 用于存储分配的指针信息

    // 查找指针
    int findPtr(void* ptr) {
        for (size_t i = 0; i < memMap.size(); ++i) {
            if (memMap[i].ptr == ptr) return i;
        }
        return -1;
    }

    // 删除指针
    void delPtr(void* ptr) {
        int pos = findPtr(ptr);
        assert(pos >= 0);
        memMap.erase(memMap.begin() + pos);
    }

    struct Sentinel {   // 用于析构时检查内存泄漏
        ~Sentinel() {
            if (!memMap.empty()) {
                cout << "Leaked memory at: " << endl;
                for (const auto& i : memMap) {
                    cout << "\t" << i.ptr << " (file: " << i.file << ", line: " << i.line << ")\n";
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
        if (memMap.size() == MAXPTRS) {
            cout << "Memory limit exceeded!(increase MAXPTRS)" << endl;
            exit(1);
        }
        memMap.emplace_back(ptr, file, line);
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
        assert(!memMap.empty());
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