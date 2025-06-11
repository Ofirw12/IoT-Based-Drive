
#include <cstdlib>
#include <thread>
#include <iostream>
#include "test_macros.h"
#include "WaitableQueue.hpp"

template<typename T>
class MyQueue
{
public:
    void push(T value) {m_queue.push_back(value);}
    void pop() {m_queue.pop_back();}
    T front() {return m_queue.front();}
    bool empty() const { return m_queue.empty();}
private:
    std::vector<T> m_queue;
};

static std::atomic<int> counter = 0;

template <typename Q>
void Writer(ilrd::WaitableQueue<int, Q>& q)
{

    for( int i = 0; i < 10; ++i)
    {
        q.Push(counter.fetch_add(1));
    }
    std::cout << "Writer thread " << std::this_thread::get_id() <<
        " done. waiting for join" << std::endl;
}
template <typename Q>
void Reader(ilrd::WaitableQueue<int, Q>& q)
{
    int val = 0;
    for( int i = 0; i < 10; ++i)
    {
        if (rand() % 2)
        {
            q.Pop(val);
        }
        else if(!q.Pop(std::chrono::milliseconds(100), val))
        {
            --i;
        }


        std::cout << "val read: " << val << std::endl;
    }
    std::cout << "Reader thread " << std::this_thread::get_id() <<
    " done. waiting for join" << std::endl;
}

template <typename Q>
void TestWaitableQueue()
{
    const size_t thread_count = 10;
    std::thread readers[thread_count] = {};
    std::thread writers[thread_count] = {};
    ilrd::WaitableQueue<int, Q> queue;
    for (int i = 0; i < thread_count; i++)
    {
        readers[i] = std::thread([&queue]() { Reader(queue); });
        writers[i] = std::thread([&queue]() { Writer(queue); });
    }

    for( int i = 0; i < thread_count; ++i)
    {
        readers[i].join();
        writers[i].join();
    }

    TEST("WaitableQueue Is done", queue.IsEmpty(), true);

}

int main()
{
    TestWaitableQueue<std::queue<int>>();
    TestWaitableQueue<MyQueue<int>>();
    TestWaitableQueue<std::priority_queue<int>>();

    PASS;
    return 0;
}