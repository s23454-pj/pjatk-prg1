#include <iostream>
#include <string>


auto main(int, char* argv[]) -> int
{
    auto const typed_password = argv[1];

    std::cout << "password: ";
    auto password = std::string{};
    std::getline(std::cin, password);

    while (typed_password != password) {
        std::cout << "password: ";
        std::cin >> password;
    }
    std::cout << "OK!";
    return 0;
}