#ifndef S23454_STUDENT_H
#define S23454_STUDENT_H

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
}  // namespace s23454

#endif
