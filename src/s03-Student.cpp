#include "iostream"
#include "s23454/Student.h"
#include "sstream"

s23454::Student::Student(std::string first_name,
                         std::string last_name,
                         std::string index_number,
                         int semester,
                         double notes_avg)
        : first_name{first_name}
        , last_name{last_name}
        , index_number{index_number}
        , semester{semester}
        , notes_avg{notes_avg}

{}

auto main() -> int
{
    auto student = s23454::Student("K", "J", "s23454", 1, 4.5);
    std::cout << student.to_string();
    return 0;
}