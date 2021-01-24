#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <random>
#include <thread>

auto print(std::mutex& mtx,
           std::condition_variable& cv,
           const std::string th_action,
           int& current_number) -> void
{
    std::cout << "Thread: " << th_action << " started." << std::endl;
    std::random_device rd;
    std ::uniform_int_distribution<int> random_number(1, 42);

    std::unique_lock lck{mtx};
    while (current_number <= 1024) {
        cv.wait(lck);
        auto add_number = random_number(rd);
        current_number  = current_number + add_number;
        std::cout << th_action << ": " << current_number << "\n";

        cv.notify_one();
    };
}


auto main() -> int
{
    std::mutex mtx;
    std::condition_variable cv;
    std::string provided_number;
    auto current_number = 0;

    auto th_ping = std::thread(
        print, std::ref(mtx), std::ref(cv), "Ping: ", std::ref(current_number));

    auto th_pong = std::thread(
        print, std::ref(mtx), std::ref(cv), "Pong: ", std::ref(current_number));

    std::getline(std::cin, provided_number);
    current_number = std::stoi(provided_number);
    cv.notify_all();

    th_ping.join();
    th_pong.join();

    return 0;
}
