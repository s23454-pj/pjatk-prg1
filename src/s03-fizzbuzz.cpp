#include <iostream>
#include <string>


auto main(int, char* argv[]) -> int
{
    auto const number = std::stoi(argv[1]);

    for (int i = 1; i <= number; ++i) {
        std::cout << i << " ";

        if (i % 3 == 0) {
            std::cout << "Fizz\n";
        } else if (i % 5 == 0) {
            std::cout << "Buzz\n";
        } else {
            std::cout << "FizzBuzz\n";
        }
    }

    return 0;
}