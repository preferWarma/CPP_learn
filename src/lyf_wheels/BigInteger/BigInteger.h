#ifndef BIGINTEGER_H_
#define BIGINTEGER_H_

#include <vector>
#include <cstdint>
#include <string>

namespace lyf {
    using std::vector;
    using std::string;
    using std::ostream, std::istream;
    using std::string_view;

    class BigInteger {
        using BaseType = int;
        static constexpr int BASE_DIGITS = 4;                                       // 一个基数的有效位数(8位十进制数不会在int返回溢出)
        static constexpr int BASE = 1e4;                                            // 基数(可以视作存储进制)

        // 比较两个数组表示的大整数的值大小(a < b返回true)
        static bool absLess(const vector<BaseType>& a, const vector<BaseType>& b);
        // 计算两个数数组表示的大整数的乘积
        static vector<BaseType> multiply(const vector<BaseType>& a, const vector<BaseType>& b);

    private:
        vector<BaseType> digits;                        // 用于存储大整数(不包括符号位), 逆序存储, 低位在前, 高位在后
        bool isNegative;                                // 是否为负数(符号位)

        BigInteger(const vector<BaseType>& digits, bool isNegative)
            : digits(digits), isNegative(isNegative) {}                     // 私有构造函数
        void removeLeadingZeros();                                          // 移除前导0: 000123 -> 123, 0000 -> 0
        void parseFromString(const string& str);                            // 从字符串解析并设置当前对象的值

    public:
        BigInteger() : digits(vector<BaseType>()), isNegative(false) {}     // 默认构造函数
        BigInteger(const string& str);                                      // 从字符串构造
        BigInteger(int32_t num);                                            // 从int构造
        BigInteger(int64_t num);                                            // 从long long构造
        BigInteger(uint64_t num);                                           // 从unsigned long long构造

        string to_string() const;                                           // 转换为字符串
        friend ostream& operator<<(ostream& os, const BigInteger& bigInt);  // 重载输出运算符
        friend istream& operator>>(istream& is, BigInteger& bigInt);        // 重载输入运算符

        BigInteger operator+(const BigInteger& other) const;                // 重载加法运算符
        BigInteger operator-(const BigInteger& other) const;                // 重载减法运算符
        BigInteger operator*(const BigInteger& other) const;                // 重载乘法运算符
        BigInteger operator/(const BigInteger& other) const;                // 重载除法运算符
        BigInteger& operator+=(const BigInteger& other);                    // 重载加等于运算符
        BigInteger& operator-=(const BigInteger& other);                    // 重载减等于运算符
        BigInteger& operator*=(const BigInteger& other);                    // 重载乘等于运算符
        BigInteger& operator/=(const BigInteger& other);                    // 重载除等于运算符
        BigInteger operator%(const BigInteger& other) const;                // 重载取模运算符
        BigInteger operator-() const;                                       // 重载取负运算符

        bool operator<(const BigInteger& other) const;                      // 重载小于运算符
        bool operator>(const BigInteger& other) const;                      // 重载大于运算符
        bool operator<=(const BigInteger& other) const;                     // 重载小于等于运算符
        bool operator>=(const BigInteger& other) const;                     // 重载大于等于运算符
        bool operator==(const BigInteger& other) const;                     // 重载等于运算符
        bool operator!=(const BigInteger& other) const;                     // 重载不等于运算符

        bool isZero() const;                                                // 判断是否为0

        /// @brief 获取符号位(正数返回true, 负数返回false)
        bool getSign() const { return !isNegative; }                        // 判断是否为负数



        // 测试时使用
        const vector<BaseType>& getRawVector() const { return digits; }
        bool getIsNegative() const { return isNegative; }
    };

    // 移除前导0
    inline void BigInteger::removeLeadingZeros() {
        while (digits.size() > 1 && digits.back() == 0) {
            digits.pop_back();
        }
        if (digits.size() == 1 && digits[0] == 0) {
            isNegative = false; // 把0视为非负数
        }
    }

    inline void BigInteger::parseFromString(const string& str) {
        if (str.empty()) {
            throw std::invalid_argument("Empty string");
        }
        isNegative = (str[0] == '-');
        int start = isNegative ? 1 : 0;
        for (int i = str.size(); i > start; i -= BASE_DIGITS) {
            int end = std::max(start, i - BASE_DIGITS);
            digits.emplace_back(std::stoi(str.substr(end, i - end)));
        }
        this->removeLeadingZeros();
    }

    inline BigInteger::BigInteger(const string& str) {
        this->parseFromString(str);
    }

    inline lyf::BigInteger::BigInteger(int32_t num) {
        this->parseFromString(std::to_string(num));
    }

    inline BigInteger::BigInteger(int64_t num) {
        this->parseFromString(std::to_string(num));
    }

    inline BigInteger::BigInteger(uint64_t num) {
        this->parseFromString(std::to_string(num));
    }

    inline string BigInteger::to_string() const {
        string res;
        if (digits.empty()) {
            return "0";
        }
        if (isNegative) {
            res.push_back('-');
        }
        res.append(std::to_string(digits.back()));
        for (int i = digits.size() - 2; i >= 0; --i) {
            res.append(BASE_DIGITS - std::to_string(digits[i]).size(), '0');    // 如果不足BASE_DIGITS位, 补0
            res.append(std::to_string(digits[i]));
        }
        return res;
    }

    inline ostream& operator<<(ostream& os, const BigInteger& bigInt) {
        return os << bigInt.to_string();
    }

    inline istream& operator>>(istream& is, BigInteger& bigInt) {
        string str;
        is >> str;
        bigInt.parseFromString(str);
        return is;
    }

    inline BigInteger BigInteger::operator+(const BigInteger& other) const {
        if (isNegative == other.isNegative) {   // 同号加法
            BigInteger res;
            res.isNegative = isNegative;
            res.digits.clear();
            bool carry = false;  // 进位标志
            for (size_t i = 0; i < std::max(digits.size(), other.digits.size()) || carry; ++i) {
                if (i == res.digits.size()) {
                    res.digits.push_back(0);
                }
                res.digits[i] += carry
                    + (i < digits.size() ? digits[i] : 0)
                    + (i < other.digits.size() ? other.digits[i] : 0);
                carry = res.digits[i] >= BASE;
                if (carry) {
                    res.digits[i] -= BASE;
                }
            }
            return res;
        }
        else {
            return *this - (-other);
        }
    }

    inline BigInteger BigInteger::operator-(const BigInteger& other) const {
        if (isNegative != other.isNegative) {
            return *this + (-other);
        }
        if (*this == other) {
            return 0ULL;
        }
        // 同号减法，保证a > b
        bool thisLessOther = absLess(digits, other.digits);
        const vector<BaseType>& a = thisLessOther ? other.digits : digits;
        const vector<BaseType>& b = thisLessOther ? digits : other.digits;

        BigInteger res;
        res.isNegative = thisLessOther;
        res.digits.clear();

        bool borrow = false;    // 借位标志
        for (size_t i = 0; i < a.size() || borrow; ++i) {
            int diff = a[i] - borrow;
            if (i < b.size()) {
                diff -= b[i];
            }
            if (diff < 0) {
                diff += BASE;
                borrow = true;
            }
            else {
                borrow = false;
            }
            res.digits.push_back(diff);
        }
        res.removeLeadingZeros();
        return res;
    }

    // TODO fft优化
    inline BigInteger BigInteger::operator*(const BigInteger& other) const {
        BigInteger&& tmp = BigInteger(multiply(digits, other.digits), isNegative ^ other.isNegative);
        tmp.removeLeadingZeros();
        return tmp;
    }

    // TODO fft优化
    inline BigInteger BigInteger::operator/(const BigInteger& other) const {
        return BigInteger();
    }

    inline BigInteger& BigInteger::operator+=(const BigInteger& other) {
        auto res = *this + other;
        digits = res.digits;
        isNegative = res.isNegative;
        return *this;
    }

    inline BigInteger& BigInteger::operator-=(const BigInteger& other) {
        auto res = *this - other;
        digits = res.digits;
        isNegative = res.isNegative;
        return *this;
    }

    inline BigInteger& BigInteger::operator*=(const BigInteger& other) {
        auto res = *this * other;
        digits = res.digits;
        isNegative = res.isNegative;
        return *this;
    }

    inline BigInteger& BigInteger::operator/=(const BigInteger& other) {
        auto res = *this / other;
        digits = res.digits;
        isNegative = res.isNegative;
        return *this;
    }

    // TODO 取模运算待定
    inline BigInteger BigInteger::operator%(const BigInteger& other) const {
        return BigInteger();
    }

    inline BigInteger BigInteger::operator-() const {
        auto result = *this;
        result.isNegative = !isNegative;
        return result;
    }

    // 比较绝对值大小, 其中a和b的元素都是非负数, 当a严格小于b时返回true
    inline bool BigInteger::absLess(const vector<BaseType>& a, const vector<BaseType>& b) {
        if (a.size() != b.size()) {
            return a.size() < b.size();
        }
        // 从高位到低位比较(逆存储序，低位在前，高位在后)
        for (int i = a.size() - 1; i >= 0; --i) {
            if (a[i] != b[i]) {
                return a[i] < b[i];
            }
        }
        return false;
    }

    // TODO 待优化
    inline vector<BigInteger::BaseType> BigInteger::multiply(const vector<BaseType>& a, const vector<BaseType>& b) {
        vector<BaseType> res(a.size() + b.size() + 1, 0);
        // 逐位相乘(基于卷积操作) 低位在前, 高位在后
        for (size_t i = 0; i < a.size(); ++i) {
            for (size_t j = 0; j < b.size(); ++j) {
                res[i + j] += a[i] * b[j];  // 调整基数大小确保不会溢出
                res[i + j + 1] += res[i + j] / BASE;
                res[i + j] %= BASE;
            }
        }
        return res;
    }

    // 只需要实现小于号, 其他关系运算符都可以通过小于号实现
    inline bool BigInteger::operator<(const BigInteger& other) const {
        if (isNegative != other.isNegative) {
            return isNegative;
        }
        return absLess(digits, other.digits);
    }

    inline bool BigInteger::operator>(const BigInteger& other) const {
        return other < *this;
    }

    inline bool BigInteger::operator<=(const BigInteger& other) const {
        return !(*this > other);
    }

    inline bool BigInteger::operator>=(const BigInteger& other) const {
        return !(*this < other);
    }

    inline bool BigInteger::operator==(const BigInteger& other) const {
        return !(*this < other) && !(*this > other);
    }

    inline bool BigInteger::operator!=(const BigInteger& other) const {
        return !(*this == other);
    }

    inline bool BigInteger::isZero() const {
        return digits.size() == 0
            || (digits.size() == 1 && digits[0] == 0);
    }

}   // namespace lyf


#endif /* !BIGINTEGER_H_ */
