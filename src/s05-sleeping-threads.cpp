#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

auto handle_task(std::queue<std::string>& queue,
                 std::mutex& mtx,
                 int thread_number) -> void
{
    std::random_device rd;
    std ::uniform_int_distribution<int> random_number(1, 100);
    while (true) {
        std::lock_guard<std::mutex> lck{mtx};
        if (queue.empty()) {
            auto pause_time = random_number(rd);
            std::this_thread::sleep_for(std::chrono::milliseconds(pause_time));
            continue;
        }

        if (!queue.empty()) {
            auto value = queue.front();
            queue.pop();

            if (value == "") {
                std::cout << "thread " << thread_number << " exiting\n";
                return;
            } else {
                std::cout << "Thread: " << thread_number
                          << " Value 1: " << value << std::endl;
            }
        }
    }
}

auto main() -> int
{
    std::mutex mtx;
    auto my_queue = std::queue<std::string>();
    std::string my_text;
    auto const THREADS_COUNTER = 2;

    std::vector<std::unique_ptr<std::thread>> tv;
    for (auto i = 0; i < THREADS_COUNTER; ++i) {
        auto my_thread = std::make_unique<std::thread>(
            handle_task, std::ref(my_queue), std::ref(mtx), i + 1);
        tv.push_back(std::move(my_thread));
    }


    auto empty_string_counter = 0;
    while (true) {
        std::getline(std::cin, my_text);
        my_queue.push(my_text);

        if (my_text == "") {
            ++empty_string_counter;
        }
        if (empty_string_counter == THREADS_COUNTER) {
            break;
        }
    }


    for (auto& each : tv) {
        each->join();
    }


    return 0;
}
