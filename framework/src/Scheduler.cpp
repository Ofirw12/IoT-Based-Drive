
#include <mutex> // std::unique_lock

#include "Scheduler.hpp"


ilrd::Scheduler::Scheduler() : m_timer(ThreadFunc, this) {}

ilrd::Scheduler::~Scheduler()
{
    std::unique_lock lock(m_mutex);
    m_cv.wait(lock, [this]{return m_queue.empty();});
}

void ilrd::Scheduler::AddTask(const std::shared_ptr<ISchedulerTask>& task,
                              std::chrono::milliseconds from_now)
{
    std::unique_lock lock(m_mutex);
    m_queue.emplace(task, from_now);
    m_timer.SetTime(m_queue.top().GetTimePoint());
}

void ilrd::Scheduler::ThreadFunc(const sigval sval)
{
    const auto sch = static_cast<Scheduler*>(sval.sival_ptr);
    sch->HandleTask();
}

void ilrd::Scheduler::HandleTask()
{
    std::unique_lock lock(m_mutex);
    const SchedulerTask to_run = m_queue.top();
    m_queue.pop();
    lock.unlock();
    to_run.Run();
    lock.lock();
    if (!m_queue.empty())
    {
        m_timer.SetTime(m_queue.top().GetTimePoint());
    }
    else
    {
        m_cv.notify_one();
    }
}

ilrd::Scheduler::SchedulerTask::SchedulerTask(
    const std::shared_ptr<ISchedulerTask>& task, const std::chrono::milliseconds ms)
        : m_task(task), m_timeToRun(std::chrono::system_clock::now() + ms)
{}


void ilrd::Scheduler::SchedulerTask::Run() const
{
    m_task->Run();
}

std::chrono::time_point<std::chrono::system_clock>
    ilrd::Scheduler::SchedulerTask::GetTimePoint() const
{
    return m_timeToRun;
}

bool ilrd::Scheduler::SchedulerTask::operator<(const SchedulerTask& other) const
{
    return m_timeToRun > other.m_timeToRun;
}
