#include <thread>
#include <iostream>

int main()
{
    std::thread t([]()
    {
        std::cout << "Hello from thread!\n";
    });
    std::cout << "Hello from main!\n";
    t.join();
}
