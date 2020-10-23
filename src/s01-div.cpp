#include <iostream>


auto main(int, char* argv[]) -> int
{
    auto const a = std::stof(argv[1]);
    auto const b = std::stof(argv[2]);
    std::cout << a / b << std::endl;

    return 0;
}