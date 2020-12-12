#include <array>
#include <iostream>

auto main() -> int
{
    auto rows = 50;
    for (auto i = 1; i <= rows; ++i) {
        std::cout << std::string(i, '*') << "\n";
    }

    return 0;
}
