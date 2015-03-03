#include <thread>
#include <iostream>
#include <vector>

void main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 16; ++i)
    {
        threads.emplace_back([i]()
        {
            std::cout << "Hello from thread " << i << "!\n";
        });
    }
    std::cout << "Hello from main!\n";
    for (auto & t: threads)
        t.join();
}