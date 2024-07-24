#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstddef>
#include <new>
#include <unordered_map>
#include <fstream>
#include "MemCheck.h"

using std::size_t;
using std::cout, std::endl;
using std::unordered_map;
using std::string;

#undef new  // 取消new宏定义

bool __traceFlag = true;
bool __activeFlag = false;
std::ofstream __fileStream;
memCheck::LogType __logType = memCheck::LogType::Just_Cout;

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
                if (__logType != memCheck::LogType::Just_Cout) {
                    __fileStream << "Leaked memory at: " << endl;
                }
                if (__logType != memCheck::LogType::Just_File) {
                    cout << "Leaked memory at: " << endl;
                }
                for (const auto& [ptr, info] : memMap) {
                    if (__logType != memCheck::LogType::Just_Cout) {
                        __fileStream << "\t" << ptr << " with size: " << info.size
                            << " (file: " << info.file << ", line: " << info.line << ")\n";
                    }
                    if (__logType != memCheck::LogType::Just_File) {
                        cout << "\t" << ptr << " with size: " << info.size
                            << " (file: " << info.file << ", line: " << info.line << ")\n";
                    }
                }
            }
            else {
                if (__logType != memCheck::LogType::Just_Cout) {
                    __fileStream << "No user memory leaks!" << endl;
                }
                if (__logType != memCheck::LogType::Just_File) {
                    cout << "No user memory leaks!" << endl;
                }
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
    if (__activeFlag) {
        if (memMap.size() == MAXPTRS) {
            if (__logType != memCheck::LogType::Just_Cout) {
                __fileStream << "Memory limit exceeded!(increase MAXPTRS)" << endl;
            }
            if (__logType != memCheck::LogType::Just_File) {
                cout << "Memory limit exceeded!(increase MAXPTRS)" << endl;
            }
            exit(1);
        }
        memMap[ptr] = { size, file, line }; // 这里在memMap内部会调用一次全局的new(因为我们已经#undef new了), 所以不会出现递归调用本函数的情况
    }
    if (__traceFlag) {
        if (__logType != memCheck::LogType::Just_Cout) {
            __fileStream << "Allocated " << size << " bytes at adress: " << ptr << " (file: " << file << "  line: " << line << ")" << endl;
        }
        if (__logType != memCheck::LogType::Just_File) {
            cout << "Allocated " << size << " bytes at adress: " << ptr << " (file: " << file << "  line: " << line << ")" << endl;
        }
    }
    return ptr;
}

void* operator new[](std::size_t size, const char* file, long line) {
    return operator new(size, file, line);
}

void operator delete(void* ptr) noexcept {
    if (memMap.find(ptr) != memMap.end()) { // 是我们重载的new分配的内存
        if (__traceFlag) {
            if (__logType != memCheck::LogType::Just_Cout) {
                __fileStream << "Deallocated memory at adress: " << ptr << endl;
            }
            if (__logType != memCheck::LogType::Just_File) {
                cout << "Deallocated memory at adress: " << ptr << endl;
            }
        }
        std::free(ptr);
        memMap.erase(ptr);  // 这里内部也调用了delete来删除map中指向ptr的那块儿内存, 会再次调用这个函数, 但是此时里面的指针不在map中
    }
    else {  // 不是我们重载的new分配的内存或者重复释放
        std::free(ptr); // 直接释放, 报错信息由free函数自己处理
    }
}

void operator delete[](void* ptr) noexcept {
    operator delete(ptr);
}

void operator delete(void* ptr, std::size_t size) noexcept {
    operator delete(ptr);
}

void operator delete[](void* ptr, std::size_t size) noexcept {
    operator delete[](ptr);
}