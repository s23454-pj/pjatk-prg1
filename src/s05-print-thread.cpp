#include <iostream>
#include <thread>


auto print_to_console(int counter) -> void
{
    std::cout << "Hello, " << counter << "!\n";
}

auto main() -> int
{
    for (auto i = 0; i <= 42; ++i) {
        auto my_thread = std::thread(print_to_console, i);
        my_thread.detach();
    }
    return 0;
}
