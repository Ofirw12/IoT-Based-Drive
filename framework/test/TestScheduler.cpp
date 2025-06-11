
#include <functional>
#include <iostream>
#include <utility>

#include "Handleton.hpp"
#include "Scheduler.hpp"

class SchedulerTask1 final : public ilrd::ISchedulerTask
{
public:
    explicit SchedulerTask1(std::function<void()> func) : m_func(std::move(func)) {}
    ~SchedulerTask1() override = default;
    void Run() override { m_func(); }

private:
    std::function<void()> m_func;
};

void TestScheduler()
{
    const auto task1 = std::make_shared<SchedulerTask1>([]{std::cout << "TestScheduler" << std::endl;});
    const auto task2 = std::make_shared<SchedulerTask1>([]{std::cout << "TestScheduler2" << std::endl;});
    ilrd::Handleton::GetInstance<ilrd::Scheduler>()->AddTask(task2, std::chrono::milliseconds(11000));
    for(size_t i = 10; i != 0; --i)
    {
        ilrd::Handleton::GetInstance<ilrd::Scheduler>()->AddTask(task1, std::chrono::milliseconds(1000 * i));
    }
}

int main()
{
    TestScheduler();
    return 0;
}