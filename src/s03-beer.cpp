#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int
{
    auto const available_beers_count = (argc > 1) ? std::stoi(argv[1]) : 99;
    for (auto beers_left_count = available_beers_count; beers_left_count > 0;
         --beers_left_count) {
        std::cout << beers_left_count << " bottles of beer on the wall, "
                  << beers_left_count << " bottles of beer. \n";
        std::cout << "Take one down, pass it around, " << beers_left_count - 1
                  << " bottles of beer on the wall...\n\n";
    }
    std::cout << "No more bottles of beer on the wall, no more bottles "
                 "of beer.\n";
    std::cout << "Go to the store and buy some more, " << available_beers_count
              << " bottles of beer on the wall...\n";
}