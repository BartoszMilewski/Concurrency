#include <thread>
#include <future>
#include <mutex>
#include <iostream>
#include <chrono>

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

class Bank
{
    Account _accts[2];
    int _minBalance;
public:
    Bank(int minBalance)
        :_minBalance(minBalance)
    {
        _accts[0].deposit(minBalance);
    }
    void transfer(int from, int to, int sum)
    {
        if (_accts[from].balance() >= sum)
        {
            _accts[from].deposit(-sum);
            //std::this_thread::sleep_for(std::chrono::milliseconds(100));
            _accts[to].deposit(sum);
        }
    }
    void assertPositive() const
    {
        if (_accts[0].balance() < 0 || _accts[1].balance() < 0)
            throw exception("Negative balance!");
    }
    void assertSolvent() const
    {
        if (_accts[0].balance() + _accts[1].balance() < _minBalance)
            throw exception("Need bailout!");
    }
};

future<void> trans(Bank & bank, int from, int to, int sum)
{
    return async(launch::async, [&](int from, int to, int sum)
    {
        bank.assertPositive();
        bank.transfer(from, to, sum);
        bank.assertSolvent();
    }, from, to, sum);
}

void test()
{
    Bank bank(10);
    vector<future<void>> futures;
    for (int i = 0; i < 1000; ++i)
    {
        futures.emplace_back(trans(bank, 0, 1, 10));
        futures.emplace_back(trans(bank, 1, 0, 10));
    }
    for (auto & fut : futures)
        fut.get();
}

void main()
{
    try
    {
        test();
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }
}