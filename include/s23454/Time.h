#ifndef S23454_TIME_H
#define S23454_TIME_H
#include "sstream"

auto prepare_unit_to_print(int unit) -> std::string
{
    if (unit < 10) {
        return "0" + std::to_string(unit);
    }
    return std::to_string(unit);
}

namespace s23454 {
struct Time {
    int hh, mm, ss;
    enum class Time_of_day { morning = 1, day = 2, evening = 3, night = 4 };

    Time(int, int, int);
    auto to_string() const -> std::string;
    auto time_of_day() const -> std::string;
    auto next_hour();
    auto next_minute();
    auto next_second();
    auto count_seconds() const -> uint64_t;
    auto count_minutes() const -> uint64_t;
    auto time_to_midnight() -> Time;
    auto operator+(Time const&) -> Time;
    auto operator-(Time const&) -> Time;
    auto operator<(Time const&) -> bool;
    auto operator>(Time const&) -> bool;
    auto operator==(Time const&) -> bool;
    auto operator!=(Time const&) -> bool;
};

auto Time::to_string() const -> std::string
{
    auto out = std::ostringstream{};
    out << prepare_unit_to_print(hh) << ":" << prepare_unit_to_print(mm) << ":"
        << prepare_unit_to_print(ss) << "\n";
    return out.str();
}

auto Time::time_of_day() const -> std::string
{
    return "Foo";
}


auto Time::next_hour()
{
    ++hh;
    if (hh > 23) {
        hh = 0;
    }
}
auto Time::next_minute()
{
    ++mm;
    if (mm > 59) {
        mm = 0;
        next_hour();
    }
}
auto Time::next_second()
{
    ++ss;
    if (ss > 59) {
        ss = 0;
        next_minute();
    }
}

auto Time::count_seconds() const -> uint64_t
{
    return ss + mm * 60 + hh * 3600;
}

auto Time::count_minutes() const -> uint64_t
{
    return ss / 60 + mm + hh * 60;
}

auto Time::time_to_midnight() -> Time
{
    int seconds = 0;
    int minutes = 0;
    int hours   = 0;

    while (ss != 0) {
        next_second();
        ++seconds;
    }
    while (mm != 0) {
        next_minute();
        ++minutes;
    }
    while (hh != 0) {
        next_hour();
        ++hours;
    }
    hh = hours;
    mm = minutes;
    ss = seconds;


    return *this;
}


auto Time::operator+(Time const& time) -> Time
{
    for (int i = 0; i < time.ss; ++i) {
        next_second();
    };
    for (int i = 0; i < time.mm; ++i) {
        next_minute();
    };
    for (int i = 0; i < time.hh; ++i) {
        next_hour();
    };
    return *this;
};

auto Time::operator-(Time const& time) -> Time
{
    auto diff_ss = ss - time.ss;
    auto diff_mm = mm - time.mm;
    auto diff_hh = hh - time.hh;

    if (diff_ss < 0) {
        --diff_mm;
        ss = 60 + diff_ss;
    }

    if (diff_mm < 0) {
        --diff_hh;
        mm = 60 + diff_mm;
    }

    if (diff_hh < 0) {
        hh = 24 + diff_hh;
    }
    return *this;
}

auto Time::operator<(Time const& time) -> bool
{
    if (hh == time.hh and mm == time.mm) {
        return ss < time.ss;
    }
    if (hh == time.hh) {
        return mm < time.hh;
    }
    return ss < time.ss;
}

auto Time::operator>(Time const& time) -> bool
{
    if (hh == time.hh and mm == time.mm) {
        return ss > time.ss;
    }
    if (hh == time.hh) {
        return mm > time.hh;
    }
    return ss > time.ss;
}
auto Time::operator==(Time const& time) -> bool
{
    return (hh == time.hh and mm == time.mm and ss == time.ss);
}


}  // namespace s23454

#endif