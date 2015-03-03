#include <thread>
#include <future>
#include <deque>
#include <mutex>
#include <condition_variable>

#include <iostream>

using namespace std;

template<class T>
class MessageQueue
{
public:
    void send(T msg)
    {
        lock_guard<mutex> lck(_mtx);
        _messages.push_front(move(msg));
        _cond.notify_one();
    }
    T receive()
    {
        unique_lock<mutex> lck(_mtx);
        _cond.wait(lck, [this] { return !_messages.empty(); });
        T msg = move(_messages.back());
        _messages.pop_back();
        return msg;
    }
private:
    mutable mutex _mtx;
    mutable condition_variable _cond;
    deque<T> _messages;
};

void main()
{
    MessageQueue<int> queue;
    future<void> fut = async([&queue] { queue.send(44); });
    int i = queue.receive();
    cout << "Received: " << i << endl;
    fut.wait();
}
