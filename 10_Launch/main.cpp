#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <vector>
#include <set>

void main()
{
    std::set<std::thread::id> set;

    std::vector<std::future<std::thread::id>> futures;
    for (int i = 0; i < 340; ++i)
        futures.emplace_back(std::async(std::launch::async, []
    {
        auto id = std::this_thread::get_id();
        std::this_thread::sleep_for(std::chrono::seconds(10));
        return id;
    }));
    auto myId = std::this_thread::get_id();
    std::cout << "Waiting in thread " << std::this_thread::get_id() << std::endl;
    for (auto & fut : futures)
    {
        auto id = fut.get();
        if (id == myId)
            std::cout << "Parent thread reuse\n";
        if (set.find(id) != set.cend())
            std::cout << "Thread reuse " << id << std::endl;
        set.insert(id);
    }     
}