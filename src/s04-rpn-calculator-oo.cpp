/*
 * A reverse-polish notation calculator.
 */

#include <RPN_calculator.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>


static auto pop_top(std::stack<double>& stack) -> double
{
    if (stack.empty()) {
        throw std::logic_error{"empty stack"};
    }
    auto element = std::move(stack.top());
    stack.pop();
    return element;
}


namespace student { namespace rpn_calculator {
Element::~Element()
{}

Literal::Literal(double const v) : value{v}
{}
auto Literal::evaluate(stack_type& stack) const -> void
{
    stack.push(value);
}

auto Print::evaluate(stack_type& stack) const -> void
{
    std::cout << stack.top() << "\n";
}

auto Addition::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for +"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a + b);
}

auto Substraction::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for -"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a - b);
}

auto Multiply::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for *"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(a * b);
}

auto Division::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for /"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(float(a) / b);
}
auto DivisionInt::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for //"};
    }
    auto const b = pop_top(stack);
    auto const a = pop_top(stack);
    stack.push(int(a / b));
}
auto Remainder::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for %"};
    }
    auto const b = int(pop_top(stack));
    auto const a = int(pop_top(stack));
    stack.push(a % b);
}
auto Pow::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for **"};
    }
    auto const b = int(pop_top(stack));
    auto const a = int(pop_top(stack));
    stack.push(pow(a, b));
}

auto Sqrt::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 1) {
        throw std::logic_error{"not enough operands for sqrt"};
    }
    auto const a = int(pop_top(stack));
    stack.push(sqrt(a));
}
auto SqrtN::evaluate(stack_type& stack) const -> void
{
    if (stack.size() < 2) {
        throw std::logic_error{"not enough operands for sqrt_n"};
    }
    auto const b = int(pop_top(stack));
    auto const a = int(pop_top(stack));
    stack.push(pow(a, 1 / b));
}

Calculator::Calculator(stack_type s) : stack{std::move(s)}
{}

auto Calculator::push(std::unique_ptr<Element> op) -> void
{
    ops.push(std::move(op));
}

auto Calculator::push(std::string each) -> void
{
    using student::rpn_calculator::Addition;
    using student::rpn_calculator::Division;
    using student::rpn_calculator::DivisionInt;
    using student::rpn_calculator::Literal;
    using student::rpn_calculator::Multiply;
    using student::rpn_calculator::Pow;
    using student::rpn_calculator::Print;
    using student::rpn_calculator::Remainder;
    using student::rpn_calculator::Sqrt;
    using student::rpn_calculator::SqrtN;
    using student::rpn_calculator::Substraction;


    if (each == "p") {
        Calculator::push(std::make_unique<Print>());
    } else if (each == "+") {
        Calculator::push(std::make_unique<Addition>());
    } else if (each == "-") {
        Calculator::push(std::make_unique<Substraction>());
    } else if (each == "*") {
        Calculator::push(std::make_unique<Multiply>());
    } else if (each == "/") {
        Calculator::push(std::make_unique<Division>());
    } else if (each == "//") {
        Calculator::push(std::make_unique<DivisionInt>());
    } else if (each == "%") {
        Calculator::push(std::make_unique<Remainder>());
    } else if (each == "**") {
        Calculator::push(std::make_unique<Pow>());
    } else if (each == "sqrt") {
        Calculator::push(std::make_unique<Sqrt>());
    } else if (each == "sqrt_n") {
        Calculator::push(std::make_unique<SqrtN>());
    } else {
        Calculator::push(std::make_unique<Literal>(std::stod(each)));
    }
}


auto Calculator::evaluate() -> void
{
    while (not ops.empty()) {
        auto op = std::move(ops.front());
        ops.pop();

        op->evaluate(stack);
    }
}
}}  // namespace student::rpn_calculator


auto make_args(int argc, char* argv[], bool const with_exec = false)
    -> std::vector<std::string>
{
    auto args         = std::vector<std::string>{};
    auto const offset = static_cast<size_t>(not with_exec);
    std::copy_n(argv + offset, argc - offset, std::back_inserter(args));
    return args;
}

auto main(int argc, char* argv[]) -> int
{
    using student::rpn_calculator::Calculator;
    auto calculator = Calculator{};

    for (auto const& each : make_args(argc, argv)) {
        try {
            calculator.push(each);
        } catch (std::logic_error const& e) {
            std::cerr << "error: " << each << ": " << e.what() << "\n";
        }
    }

    try {
        calculator.evaluate();
    } catch (std::logic_error const& e) {
        std::cerr << "error: during evaluation: " << e.what() << "\n";
    }

    return 0;
}
