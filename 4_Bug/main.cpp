#include <thread>
#include <iostream>
#include <vector>

#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

std::vector<std::thread> spawn()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 16; ++i)
    {
        threads.emplace_back([&]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * i));
            std::cout << "Hello from thread " << i << "!\n";
        });
    }
    return threads;
}

void main()
{
    std::vector<std::thread> threads;
#if 1
    for (int i = 0; i < 16; ++i)
    {
        threads.emplace_back([&]()
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10 * i));
            std::cout << "Hello from thread " << i << "!\n";
        });
    }
#else
    threads = spawn();
#endif
    std::cout << "Hello from main!\n";
    for (auto & t : threads)
        t.join();
 }