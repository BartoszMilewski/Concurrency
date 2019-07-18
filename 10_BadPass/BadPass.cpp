#include <thread>
#include <future>
#include <memory>

void threadFun(std::unique_ptr<int> p)
{}

int main()
{
    std::unique_ptr<int> up(new int(10));
    std::async(threadFun, std::move(up));
}