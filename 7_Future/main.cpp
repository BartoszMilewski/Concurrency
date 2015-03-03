#include <thread>
#include <future>
#include <iostream>
#include <string>
#include <memory>

void fun(std::promise<std::string> pr, std::unique_ptr<int> uptr)
{
    std::cout << (void *)(uptr.get()) << std::endl;
    std::cout << "Worker sending.\n";
    pr.set_value("Message from thread.");
}

void main()
{
    std::unique_ptr<int> uptr(new int(10));
    std::promise<std::string> pr;
    std::cout << (void *)(uptr.get()) << std::endl;
    std::future<std::string> fut = pr.get_future();
    std::thread th(fun, std::move(pr), std::move(uptr));
    std::cout << "Main receiving.\n";
    std::string s = fut.get();
    std::cout << s << std::endl;
    th.join();
}