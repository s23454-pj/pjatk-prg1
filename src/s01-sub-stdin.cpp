#include <iostream>
#include <string>


auto ask_user_for_integer(std::string prompt) -> int
{
    std::cout << prompt << "(int): ";
    auto number = std::string{};
    std::getline(std::cin, number);
    return std::stoi(number);
}

auto main() -> int
{
    auto const a = ask_user_for_integer("a = ");
    auto const b = ask_user_for_integer("b = ");
    std::cout << (a - b) << std::endl;

    return 0;
}