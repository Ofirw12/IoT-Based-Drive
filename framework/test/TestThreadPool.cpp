
#include <iostream>

#include "ThreadPool.hpp"
#include "test_macros.h"

using namespace ilrd::threadpool;

void Task1(int i)
{
    std::cout << i << std::endl;
}

void Task2(int i, char c)
{
    std::cout << i << std::endl;
    std::cout << c << std::endl;
}

int FutureTaskFunc(bool b)
{
    sleep(1);
    return b ? 3 : 8;
}

void TestThreadPool()
{
    ilrd::ThreadPool tp(4);

    std::function func1([] { Task1(1); });

    std::shared_ptr<ITPTask> ifunc1(new FunctionTask(func1));
    // tp.AddTask(ifunc1, ilrd::HIGH);

    std::function<void()> func2 = std::bind(Task1, 9);
    std::shared_ptr<ITPTask> ifunc2(new FunctionTask(func2));

    std::function<int()> func3 = std::bind(FutureTaskFunc, false);
    std::shared_ptr<ITPTask> ifunc3(new FutureTask(func3));

    std::function<void()> func4 = std::bind(Task2, 4, 'c');
    std::shared_ptr<ITPTask> ifunc4(new FunctionTask(func4));

    tp.AddTask(ifunc4, ilrd::ThreadPool::HIGH);

    for(size_t i = 0; i < 10; ++i)
    {
        tp.AddTask(ifunc3, ilrd::ThreadPool::HIGH);
        tp.AddTask(ifunc2, ilrd::ThreadPool::LOW); // prints 9
        tp.AddTask(ifunc1, ilrd::ThreadPool::MEDIUM); //prints 1
        std::cout << static_cast<FutureTask<int>*>(ifunc3.get())->Get() << std::endl; //prints 8
    }
    tp.SetNumThreads(8);

    for(size_t i = 0; i < 10; ++i)
    {
        tp.AddTask(ifunc2, ilrd::ThreadPool::MEDIUM);
        tp.AddTask(ifunc1, ilrd::ThreadPool::LOW);
        if (i == 5)
        {
            tp.Pause();
        }

        if (i == 8)
        {
            tp.Resume();
            std::cout << "resuming" << std::endl;
            tp.SetNumThreads(3);
        }

        tp.SetNumThreads(10);
    }
    tp.Pause();
    tp.SetNumThreads(5);

}

int main()
{
    TestThreadPool();
    PASS;
    return 0;
}