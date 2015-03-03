#include <thread>
#include <future>
#include <iostream>

struct Counter
{
    Counter(int k) : n(k) {}
    int n;
}; 

struct Holder
{
    Holder(int n) 
        : c(new Counter(n)) {}
    Counter * c;
};

void main()
{
    const Holder h(10);
    std::future<void> fut = std::async([](Holder const & h)
    {
        ++(h.c->n);
    }, std::ref(h));
    std::cout << h.c->n << std::endl;
    fut.wait();
    std::cout << h.c->n << std::endl;
}