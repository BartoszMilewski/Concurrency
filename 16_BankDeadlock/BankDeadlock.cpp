#include <thread>
#include <future>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std;

class Account
{
    mutable recursive_mutex _mutex;
    int _balance;
public:
    Account(int balance = 0) : _balance(balance) {}
    Account(Account &) = delete;
    void deposit(int sum)
    {
        lock_guard<recursive_mutex> lck(_mutex);
        _balance += sum;
    }
    int balance() const
    {
        lock_guard<recursive_mutex> lck(_mutex);
        return _balance;
    }
    recursive_mutex & getMutex()
    {
        return _mutex;
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
    void bad_transfer(int from, int to, int sum)
    {
        // recipe for deadlock
        lock_guard<recursive_mutex> lck1(_accts[from].getMutex());
        lock_guard<recursive_mutex> lck2(_accts[to].getMutex());

        if (_accts[from].balance() >= sum)
        {
            _accts[from].deposit(-sum);
            _accts[to].deposit(sum);
        }
    }
    void transfer(int from, int to, int sum)
    {
        lock(_accts[from].getMutex(), _accts[to].getMutex());
        lock_guard<recursive_mutex> lck1(_accts[from].getMutex(), adopt_lock);
        lock_guard<recursive_mutex> lck2(_accts[to].getMutex(), adopt_lock);

        if (_accts[from].balance() >= sum)
        {
            _accts[from].deposit(-sum);
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
    for (int i = 0; i < 200; ++i)
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