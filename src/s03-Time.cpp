#include "iostream"
#include "s23454/Time.h"

s23454::Time::Time(int hh, int mm, int ss) : hh{hh}, mm{mm}, ss{ss}
{}

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
    time = s23454::Time{22, 50, 10};
    std::cout << time.time_to_midnight().to_string() << "\n\n";

    return 0;
}