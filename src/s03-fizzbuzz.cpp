#include <iostream>
#include <string>

auto main(int, char* argv[]) -> int
{
    auto const number = std::stoi(argv[1]);

    for (int i = 1; i <= number; ++i) {
        std::cout << i << " " << (i % 3 ? "" : "Fizz") << (i % 5 ? "" : "Buzz")
                  << "\n";
    }

    return 0;
}