#include <thread>
#include <iostream>
#include <string>

void repeat(std::string & str, int n)
{
    if (n > 0)
    {
        str[0] = 'B';
        std::cout << str;
        repeat(str, n - 1);
    }
}

void main()
{
    //    std::thread t(repeat, "blah!", 3);
    std::string str("blah!");
    std::thread t(repeat, std::ref(str), 3);
    std::cout << "[Hello from main!]";
    t.join();
    std::cout << std::endl << str;
}
