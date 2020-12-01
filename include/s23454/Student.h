#ifndef S23454_STUDENT_H
#define S23454_STUDENT_H

#include <sstream>
#include <string>


namespace s23454 {
struct Student {
    std::string const first_name;
    std::string const last_name;
    std::string const index_number;
    int semester;
    double notes_avg;

    Student(std::string, std::string, std::string, int, double);

    auto to_string() const -> std::string;
};

auto Student::to_string() const -> std::string
{
    auto out = std::ostringstream{};
    out << "First name: " << first_name << "\n"
        << "Last name: " << last_name << "\n"
        << "Index number: " << index_number << "\n"
        << "Semester: " << semester << "\n"
        << "Notes average: " << notes_avg << "\n";


    return out.str();
}
}  // namespace s23454

#endif