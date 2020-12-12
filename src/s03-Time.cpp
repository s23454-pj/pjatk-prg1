#include <s23454/Time.h>

#include <iomanip>
#include <iostream>
#include <sstream>
s23454::Time::Time(int hh, int mm, int ss) : hh{hh}, mm{mm}, ss{ss}
{}


auto prepare_unit_to_print(int unit) -> std::string
{
    auto out = std::ostringstream{};
    out << std::setfill('0') << std::setw(2) << unit;
    return out.str();
}

auto s23454::Time::to_string() const -> std::string
{
    auto out = std::ostringstream{};
    out << prepare_unit_to_print(hh) << ":" << prepare_unit_to_print(mm) << ":"
        << prepare_unit_to_print(ss) << "\n";
    return out.str();
}

auto s23454::Time::to_string(const Time_of_day time_of_day) -> std::string
{
    switch (time_of_day) {
    case Time_of_day::morning:
        return "Morning\n";
    case Time_of_day::day:
        return "Day\n";
    case Time_of_day::evening:
        return "Evening\n";
    case Time_of_day::night:
        return "Night\n";
    }
}


auto s23454::Time::time_of_day() const -> Time::Time_of_day
{
    if (hh <= 5) {
        return Time_of_day::night;
    } else if (hh <= 10) {
        return Time_of_day::morning;
    } else if (hh <= 18) {
        return Time_of_day::day;
    } else if (hh <= 22) {
        return Time_of_day::evening;
    } else {
        return Time_of_day::night;
    }
}


auto s23454::Time::next_hour()
{
    ++hh;
    if (hh > 23) {
        hh = 0;
    }
}
auto s23454::Time::next_minute()
{
    ++mm;
    if (mm > 59) {
        mm = 0;
        next_hour();
    }
}
auto s23454::Time::next_second()
{
    ++ss;
    if (ss > 59) {
        ss = 0;
        next_minute();
    }
}

auto s23454::Time::count_seconds() const -> uint64_t
{
    return ss + mm * 60 + hh * 3600;
}


auto s23454::Time::count_minutes() const -> uint64_t
{
    return ss / 60 + mm + hh * 60;
}

auto s23454::Time::time_to_midnight() -> Time
{
    return Time{0, 0, 0} - *this;
}


auto s23454::Time::operator+(Time const& time) -> Time
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

auto s23454::Time::operator-(Time const& time) -> Time
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

auto s23454::Time::operator<(Time const& time) -> bool
{
    if (hh == time.hh and mm == time.mm) {
        return ss < time.ss;
    }
    if (hh == time.hh) {
        return mm < time.hh;
    }
    return ss < time.ss;
}

auto s23454::Time::operator>(Time const& time) -> bool
{
    if (hh == time.hh and mm == time.mm) {
        return ss > time.ss;
    }
    if (hh == time.hh) {
        return mm > time.hh;
    }
    return ss > time.ss;
}
auto s23454::Time::operator==(Time const& time) -> bool
{
    return (hh == time.hh and mm == time.mm and ss == time.ss);
}


auto main() -> int
{
    std::cout << "to_string()\n";
    auto time = s23454::Time{23, 59, 59};
    std::cout << time.to_string() << "\n\n";

    std::cout << "next_hour()\n";
    time = s23454::Time{23, 59, 59};
    time.next_hour();
    std::cout << time.to_string() << "\n\n";

    std::cout << "next_minute()\n";
    time = s23454::Time{23, 59, 59};
    time.next_minute();
    std::cout << time.to_string() << "\n\n";

    std::cout << "next_second()\n";
    time = s23454::Time{23, 59, 59};
    time.next_second();
    std::cout << time.to_string() << "\n\n";

    std::cout << "time_of_day()\n";
    time = s23454::Time{23, 59, 59};
    std::cout << time.to_string(time.time_of_day()) << "\n";

    std::cout << "+\n";
    auto a = s23454::Time{23, 59, 59};
    auto b = s23454::Time{0, 0, 1};
    std::cout << (a + b).to_string() << "\n\n";

    std::cout << "-\n";
    a = s23454::Time{3, 59, 59};
    b = s23454::Time{4, 0, 0};
    std::cout << (a - b).to_string() << "\n\n";

    std::cout << ">\n";
    a = s23454::Time{23, 59, 59};
    b = s23454::Time{0, 0, 1};
    if (a > b) {
        std::cout << a.to_string() << " > " << b.to_string() << "\n\n";
    } else {
        std::cout << a.to_string() << " ? " << b.to_string() << "\n\n";
    }

    std::cout << "==\n";
    a = s23454::Time{23, 59, 59};
    b = s23454::Time{0, 0, 1};
    if (a == b) {
        std::cout << a.to_string() << " == " << b.to_string() << "\n\n";
    } else {
        std::cout << a.to_string() << " != " << b.to_string() << "\n\n";
    }

    std::cout << "count_seconds()\n";
    time = s23454::Time{23, 59, 59};
    std::cout << time.count_seconds() << "\n\n";

    std::cout << "count_minutes()\n";
    time = s23454::Time{23, 59, 59};
    std::cout << time.count_minutes() << "\n\n";

    std::cout << "time_to_midnight()\n";
    time = s23454::Time{23, 59, 59};
    std::cout << time.time_to_midnight().to_string();

    return 0;
}
