#include <thread>
#include <future>
#include <iostream>
#include <string>

void fun(std::promise<std::string> && pr)
{
    try
    {
        std::cout << "Worker throwing.\n";
        throw std::exception("Exception from thread.");
    }
    catch (...)
    {
        pr.set_exception(std::current_exception());
    }
}

void main()
{
    std::promise<std::string> pr;
    std::future<std::string> fut = pr.get_future();
    std::thread th(fun, std::move(pr));
    std::cout << "Main receiving.\n";
    try
    {
        std::string s = fut.get();
        std::cout << s << std::endl;
    }
    catch (std::exception e)
    {
        std::cout << "Caught: " << e.what() << std::endl;
    }
    th.join();
}