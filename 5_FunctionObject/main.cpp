#include <thread>
#include <iostream>
#include <vector>

class FunObj
{
public:
    FunObj(int i) : _i(i)
    {}
    void operator()()
    {
        std::cout << "Hello from thread " << _i << "!\n";
    }
private:
    int _i;
};

void main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 16; ++i)
    {
        threads.emplace_back(FunObj(i));
    }
    std::cout << "Hello from main!\n";
    for (auto & t: threads)
        t.join();
}