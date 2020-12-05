#ifndef S23454_TIME_H
#define S23454_TIME_H
#include <iostream>

namespace s23454 {
struct Time {
    int hh, mm, ss;
    enum class Time_of_day { morning, day, evening, night };

    Time(int, int, int);
    static auto to_string(Time_of_day const) -> std::string;
    auto to_string() const -> std::string;
    auto time_of_day() const -> Time_of_day;
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

}  // namespace s23454

#endif
