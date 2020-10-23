#include <iostream>


auto main(int argc, char* argv[]) -> int
{
    (void)argc;
    auto const a = std::stof(argv[1]);
    auto const b = std::stof(argv[2]);
    std::cout << a / b << std::endl;

    return 0;
}