#include <iostream>
#include <string>


auto main(int, char* argv[]) -> int
{
    auto const counter = std::stoi(argv[1]);
    for (auto i = counter; i != 0; i = (i > 0) ? --i : ++i) {
        std::cout << i << std::endl;
    }
    std::cout << 0 << std::endl;

    return 0;
}