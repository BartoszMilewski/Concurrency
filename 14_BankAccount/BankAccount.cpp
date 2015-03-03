#include <thread>
#include <future>
#include <mutex>
#include <iostream>

using namespace std;

class Account
{
    mutable mutex _mutex;
    int _balance;
public:
    Account(int balance = 0) : _balance(balance) {}
    Account(Account &) = delete;
    void deposit(int sum)
    {
        lock_guard<mutex> lck(_mutex);
        _balance += sum;
    }
    int balance() const
    {
        lock_guard<mutex> lck(_mutex);
        return _balance;
    }
};

future<void> depositor(Account & acct, int sum)
{
    return async([&](int sum)
    {
        acct.deposit(sum);
    }, sum);
}

future<void> balancer(Account const & acct)
{
    return async([&]()
    {
        cout << acct.balance() << endl;
    });
}

void test()
{
    Account acct;
    vector<future<void>> futures;
    futures.emplace_back(depositor(acct, 10));
    futures.emplace_back(depositor(acct, 20));
    futures.emplace_back(depositor(acct, -10));
    futures.emplace_back(balancer(acct));
    futures.emplace_back(depositor(acct, -10));
    futures.emplace_back(depositor(acct, -10));
    for (auto & fut : futures)
        fut.wait();
    cout << "Final balance " << acct.balance() << endl;
}

void main()
{
    test();
}