#ifndef RPN_CALCULATOR
#define RPN_CALCULATOR
#include "iostream"
#include "vector"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <string>

namespace s23454 {

struct Calculator {
    std::vector<std::string> arguments;
    std::stack<double> stack;

    Calculator(std::vector<std::string>);

    auto calculate() -> float;

  private:
    auto evaluate_addition() -> void;
    auto evaluate_subtraction() -> void;
    auto evaluate_multiply() -> void;
    auto evaluate_division() -> void;
    auto evaluate_division_int() -> void;
    auto evaluate_division_void() -> void;
    auto evaluate_remainder() -> void;
    auto evaluate_pow() -> void;
    auto evaluate_sqrt() -> void;
    auto evaluate_sqrt_n() -> void;
    auto pop_top() -> double;
};

auto Calculator::pop_top() -> double
{
    if (stack.empty()) {
        throw std::logic_error{"empty stack"};
    }
    auto element = std::move(stack.top());
    stack.pop();
    return element;
}

auto Calculator::evaluate_addition() -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for +"};
    }
    auto const b = pop_top();
    auto const a = pop_top();
    stack.push(a + b);
}
auto Calculator::evaluate_subtraction() -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for -"};
    }
    auto const b = pop_top();
    auto const a = pop_top();
    stack.push(a - b);
}

auto Calculator::evaluate_multiply() -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for *"};
    }
    auto const b = pop_top();
    auto const a = pop_top();
    stack.push(a * b);
}

auto Calculator::evaluate_division() -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for /"};
    }
    auto const b = pop_top();
    auto const a = pop_top();
    stack.push(float(a) / b);
}

auto Calculator::evaluate_division_int() -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for //"};
    }
    auto const b = pop_top();
    auto const a = pop_top();
    stack.push(int(a / b));
}
auto Calculator::evaluate_remainder() -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for %"};
    }
    auto const b = int(pop_top());
    auto const a = int(pop_top());
    stack.push(a % b);
}
auto Calculator::evaluate_pow() -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for **"};
    }
    auto const b = pop_top();
    auto const a = pop_top();
    stack.push(pow(a, b));
}
auto Calculator::evaluate_sqrt() -> void
{
    if (stack.size() < 1) {
        throw std::logic_error{"not enough operands for sqrt"};
    }
    auto const a = pop_top();
    stack.push(sqrt(a));
}

auto Calculator::evaluate_sqrt_n() -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for sqrt_n"};
    }
    auto const b = pop_top();
    auto const a = pop_top();
    stack.push(pow(a, 1 / b));
}

auto Calculator::calculate() -> float
{
    for (auto const argument : arguments) {
        try {
            if (argument == "p") {
                std::cout << pop_top() << "\n";
            } else if (argument == "+") {
                Calculator::evaluate_addition();
            } else if (argument == "-") {
                Calculator::evaluate_subtraction();
            } else if (argument == "*") {
                Calculator::evaluate_multiply();
            } else if (argument == "/") {
                Calculator::evaluate_division();
            } else if (argument == "//") {
                Calculator::evaluate_division_int();
            } else if (argument == "%") {
                Calculator::evaluate_remainder();
            } else if (argument == "**") {
                Calculator::evaluate_pow();
            } else if (argument == "sqrt") {
                Calculator::evaluate_sqrt();
            } else if (argument == "sqrt_n") {
                Calculator::evaluate_sqrt_n();
            } else {
                stack.push(std::stod(argument));
            }
        } catch (std::logic_error const& error) {
            std::cerr << "error: " << argument << ": " << error.what() << "\n";
        }
    }
    return pop_top();
}
}  // namespace s23454


#endif
