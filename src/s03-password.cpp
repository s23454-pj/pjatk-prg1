#include <iostream>
#include <string>


auto main(int, char* argv[]) -> int
{
    std::string password;
    do {
        std::cout << "password: ";
        std::getline(std::cin, password);
    } while (password.compare(argv[1]));
    std::cout << "OK!";
    return 0;
}