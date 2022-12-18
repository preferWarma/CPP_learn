#include <iostream>
#include <cstdarg>

template <typename T>
inline T max(T t) {
    return t;
}
// 例: 一个python风格的max函数 (万能引用，可变模板参数，完美转发)
template <typename T, typename... Rest>
inline T max(T &&t, Rest &&... rest) {
    if (sizeof... (rest) == 0)
        return t;
    else
        return std::max(t, max(std::forward<Rest>(rest)...));
}

void my_printf(const char *format, ...) {   // 可变参数函数的使用
    va_list ap; // 可变参数列表
    va_start(ap, format); // 初始化可变参数列表, ap指向第一个可变参数
    while (*format) {
        if (*format == '%') {
            format++;
            if (*format == 'd') {
                int i = va_arg(ap, int);
                std::cout << i;
            } else if (*format == 's') {
                const char *s = va_arg(ap, const char *);
                std::cout << s;
            } else if (*format == 'c') {
                // 在可变长参数中, 需要注意字节对齐。也就是float类型被扩展成double; char, short被扩展成int。
                // 因此, 如果你要去可变长参数列表中原来为float类型的参数, 需要用va_arg(argp, double)。
                // 对char和short类型的则用va_arg(argp, int)。
                char c = va_arg(ap, int);
                std::cout << c;
            } else if (*format == 'f') {
                double d = va_arg(ap, double);
                std::cout << d;
            } else {
                std::cout << "%";
            }
        } else {
            std::cout << *format;
        }
        format++;
    }
    va_end(ap); // 清理可变参数列表
}

int main() {
    std::cout << max(1, 2, 3, 4, 5) << std::endl;
    my_printf("%d %s %c", 1, "hello", 'a');
    return 0;
}