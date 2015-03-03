#include <thread>
#include <future>
#include <atomic>
#include <list>
#include <iostream>

using namespace std;

class List
{
    class Node
    {
        int _data;
        Node * _next;
    public:
        Node(int data, Node * next)
            : _data(data), _next(next)
        {}
        Node * getNext() const
        {
            return _next;
        }
    };

    atomic<Node *> _head;

public:
    List() : _head(nullptr)
    {}
    // Notice: This code contains atomicity violation
    // Don't use in production
    void push(int data)
    {
        Node * node = new Node(data, _head);
        _head = node;
    }
    /*
    void push(int data)
    {
        Node * oldHead = _head.load();
        Node * node = new Node(data, oldHead);
        _head.store(node);
    }
    */
    bool empty() const
    {
        return _head.load() == nullptr;
    }
    // Warning: this is not thread safe
    // Use only with a single thread
    void pop()
    {
        Node * top = _head.load();
        _head = _head.load()->getNext();
        delete top;
    }
};

void main()
{
    List list;
    std::list<future<void>> futures;
    for (int i = 0; i < 10000; ++i)
    {
        futures.emplace_front(async(launch::async, [&list](int i)
        {
            list.push(i);
        }, i));
    }
    while (!futures.empty())
    {
        futures.back().get();
        futures.pop_back();
    }
    int len = 0;
    while (!list.empty())
    {
       ++len;
       list.pop();
    }
    cout << len << endl;
}
