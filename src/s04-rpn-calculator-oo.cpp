#include "RPN_calculator.h"
#include "iostream"
#include "vector"


s23454::Calculator::Calculator(std::vector<std::string> arguments)
        : arguments(arguments)
{}


auto make_args(int argc, char* argv[]) -> std::vector<std::string>
{
    auto args = std::vector<std::string>{};
    std::copy_n(argv, argc, std::back_inserter(args));
    return args;
}

auto main(int argc, char* argv[]) -> int
{
    auto const args = make_args(argc - 1, argv + 1);

    auto calc = s23454::Calculator{args};
    std::cout << calc.calculate();
}
