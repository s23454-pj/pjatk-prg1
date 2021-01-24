#include <iostream>
#include <thread>


auto print_to_console(int group_counter, int thread_counter) -> void
{
    std::cout << "Thread: " << group_counter << ". Hello, " << thread_counter
              << "!" << std::endl;
}


auto invoke_group_thread(int group_counter) -> void
{
    for (auto thread_counter = 0; thread_counter <= 6; ++thread_counter) {
        auto print_thread =
            std::thread(print_to_console, group_counter, thread_counter);
        print_thread.detach();
    }
}

auto main() -> int
{
    for (auto group_counter = 0; group_counter <= 7; ++group_counter) {
        auto invoke_thread = std::thread(invoke_group_thread, group_counter);
        invoke_thread.join();
    }

    return 0;
}
