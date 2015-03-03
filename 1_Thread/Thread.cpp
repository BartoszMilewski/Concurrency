#include <thread>
#include <iostream>

void threadFun()
{
    std::cout << "Hello from thread!\n";
}

void main()
{
    std::thread t(threadFun);
    std::cout << "Hello from main!\n";
    t.join();
}
