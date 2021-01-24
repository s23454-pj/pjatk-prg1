#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>


auto take_value_from_queue(std::queue<int>& queue, int thread_id) -> void
{
    std::cout << "from thread " << thread_id << ": " << queue.front()
              << std::endl;
    queue.pop();
}

auto invoke_thread(std::queue<int>& queue, std::mutex& mtx, int thread_number)
    -> void
{
    while (true) {
        std::this_thread::sleep_for(std::chrono::microseconds(1));
        std::lock_guard<std::mutex> lck{mtx};
        if (queue.empty()) {
            return;
        }
        take_value_from_queue(queue, thread_number);
    }
}

auto main() -> int
{
    std::mutex mtx;
    auto my_queue = std::queue<int>();
    for (auto i = 1; i <= 100; ++i) {
        my_queue.push(i);
    }

    std::vector<std::unique_ptr<std::thread>> tv;

    for (auto i = 0; i <= 4; ++i) {
        auto my_thread = std::make_unique<std::thread>(
            invoke_thread, std::ref(my_queue), std::ref(mtx), i + 1);
        tv.push_back(std::move(my_thread));
    }

    for (auto& each : tv) {
        each->join();
    }
    return 0;
}
