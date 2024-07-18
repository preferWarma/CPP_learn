#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <chrono>
#include <ctime>

namespace lyf {

    class DateTime {
    private:
        using time_point = std::chrono::system_clock::time_point;
        using system_clock = std::chrono::system_clock;
        using time_t = std::time_t;

        time_point timePoint;   // 时间戳
        int year;               // 年
        int month;              // 月
        int day;                // 日
        int hour;               // 时
        int minute;             // 分
        int second;             // 秒

    public:
        DateTime(time_point timePoint) : timePoint(timePoint) {
            time_t tt = system_clock::to_time_t(timePoint);
            tm* ptm = std::localtime(&tt);  // 将时间戳转换为本地时间
            year = ptm->tm_year + 1900;
            month = ptm->tm_mon + 1;
            day = ptm->tm_mday;
            hour = ptm->tm_hour;
            minute = ptm->tm_min;
            second = ptm->tm_sec;
        }


        // 默认构造函数，使用当前时间
        DateTime() : DateTime(system_clock::now()) {}

        // 有参构造函数，使用时间戳构造
        DateTime(time_t timestamp) {
            timePoint = system_clock::from_time_t(timestamp);
            tm* ptm = std::localtime(&timestamp);
            year = ptm->tm_year + 1900;
            month = ptm->tm_mon + 1;
            day = ptm->tm_mday;
            hour = ptm->tm_hour;
            minute = ptm->tm_min;
            second = ptm->tm_sec;
        }

        // 使用年月日时分秒构造
        DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0)
            : year(year), month(month), day(day), hour(hour), minute(minute), second(second) {
            tm t;
            t.tm_year = year - 1900;
            t.tm_mon = month - 1;
            t.tm_mday = day;
            t.tm_hour = hour;
            t.tm_min = minute;
            t.tm_sec = second;
            timePoint = system_clock::from_time_t(std::mktime(&t));
        }

        // 返回时间戳
        time_t toTimestamp() const {
            return system_clock::to_time_t(timePoint);
        }

        // 年月日时分秒的get方法
        int getYear() const noexcept { return year; }
        int getMonth() const noexcept { return month; }
        int getDay() const noexcept { return day; }
        int getHour() const noexcept { return hour; }
        int getMinute() const noexcept { return minute; }
        int getSecond() const noexcept { return second; }

        // timepoint的get方法
        time_point getTimePoint() const noexcept { return timePoint; }

        // 重载<<运算符
        friend std::ostream& operator<<(std::ostream& os, const DateTime& dt) {
            time_t tt = system_clock::to_time_t(dt.timePoint);
            //格式 2024-6-24 9:54:36
            return os << dt.year << "-" << dt.month << "-" << dt.day << " "
                << dt.hour << ":" << dt.minute << ":" << dt.second << std::endl;
        }

        // 重载==运算符
        bool operator==(const DateTime& other) const {
            return timePoint == other.timePoint;
        }

        // 重载+=运算符
        DateTime& operator+=(const std::chrono::seconds& duration) {
            timePoint += duration;
            return *this;
        }

        // 重载-=运算符
        DateTime& operator-=(const std::chrono::seconds& duration) {
            timePoint -= duration;
            return *this;
        }

        // 重载+运算符
        DateTime operator+(const std::chrono::seconds& duration) const {
            return DateTime{ system_clock::to_time_t(timePoint + duration) };
        }

        // 重载-运算符
        DateTime operator-(const std::chrono::seconds& duration) const {
            return DateTime{ system_clock::to_time_t(timePoint - duration) };
        }

        // 重载<=运算符
        bool operator<=(const DateTime& other) const {
            return timePoint <= other.timePoint;
        }

        // 重载>=运算符
        bool operator>=(const DateTime& other) const {
            return timePoint >= other.timePoint;
        }

        // 重载<运算符
        bool operator<(const DateTime& other) const {
            return timePoint < other.timePoint;
        }

        // 重载>运算符
        bool operator>(const DateTime& other) const {
            return timePoint > other.timePoint;
        }
    };  // class DateTime
}   // namespace lyf

#endif // DATETIME_H