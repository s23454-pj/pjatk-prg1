#include <iostream>
#include <random>
#include <string>


auto main() -> int
{
    std::random_device rd;
    std ::uniform_int_distribution<int> random_number(1, 100);
    auto const guess_number = random_number(rd);

    auto provided_number = std::string{};
    auto number          = int{};

    do {
        std::cout << "guess: ";
        std::getline(std::cin, provided_number);
        number = std::stoi(provided_number);

        if (number > guess_number) {
            std::cout << "number too big!\n";
        } else if (number < guess_number) {
            std::cout << "number to small!\n";
        }
    } while (number != guess_number);

    std::cout << "just right!";

    return 0;
}