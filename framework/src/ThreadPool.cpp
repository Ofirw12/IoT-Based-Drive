
#include "ThreadPool.hpp"

using namespace ilrd::threadpool;
thread_local bool ilrd::ThreadPool::m_threadIsRunning = true;
const std::shared_ptr<ITPTask> ilrd::ThreadPool::m_setOffFunc =
    std::make_shared<FunctionTask<>>([] {m_threadIsRunning = false;});

enum PrivatePriority
{
    KILL = 0,
    PAUSE = 4,
    REMOVE = 5
};

ilrd::ThreadPool::ThreadPool(const size_t numThreads) :m_pauseTask(new PauseTask),
                                                    m_isRunning(true)
{
    for (size_t i = 0; i < numThreads; ++i)
    {
        auto ptr = std::make_unique<std::jthread>([this] {RunThread();});
        m_threads[ptr->get_id()].swap(ptr);
    }
}

ilrd::ThreadPool::~ThreadPool()
{
    Resume();
    for (size_t i = 0; i < m_threads.size(); ++i)
    {
        AddTask(m_setOffFunc, static_cast<Priority>(KILL));
    }
}

void ilrd::ThreadPool::AddTask(const std::shared_ptr<ITPTask>& task, const Priority priority)
{
    m_taskQueue.Push(TPTask(task, static_cast<unsigned int>(priority)));
}

void ilrd::ThreadPool::SetNumThreads(const size_t numThreads)
{
    if (const size_t curr_numThreads = m_threads.size(); numThreads > curr_numThreads)
    {
        for (size_t i = curr_numThreads; i < numThreads; ++i)
        {
            auto ptr = std::make_unique<std::jthread>(
                [this] {RunThread();});
            m_threads[ptr->get_id()].swap(ptr);
            if (!m_isRunning)
            {
                AddTask(m_pauseTask, static_cast<Priority>(PAUSE));
                m_pauseTask->Acquire();
            }
        }
    }
    else
    {
        for (size_t i = 0; i < curr_numThreads - numThreads; ++i)
        {
            AddTask(m_setOffFunc, static_cast<Priority>(REMOVE));
            m_pauseTask->NotifyOne();
        }
        for(size_t i = 0; i < curr_numThreads - numThreads; ++i)
        {
            std::thread::id tid;
            m_toRemove.Pop(tid);
            m_threads.erase(tid);
        }
    }
}

void ilrd::ThreadPool::Pause()
{
    if(!m_isRunning)
    {
        return;
    }

    m_isRunning = false;
    for(size_t i = 0; i < m_threads.size(); ++i)
    {
        AddTask(m_pauseTask, static_cast<Priority>(PAUSE));
    }

    for(size_t i = 0; i < m_threads.size(); ++i)
    {
        m_pauseTask->Acquire();
    }
}

void ilrd::ThreadPool::Resume()
{
    m_isRunning = true;
    m_pauseTask->Notify();
}

ilrd::ThreadPool::TPTask::TPTask(const std::shared_ptr<ITPTask>& task,
                                const unsigned int priority)
    : m_task(task), m_priority(priority),
        m_start(std::chrono::steady_clock::now()) {}

bool ilrd::ThreadPool::TPTask::operator<(const TPTask& other) const
{
    return (m_priority == other.m_priority) ?
        (m_start > other.m_start) : (m_priority < other.m_priority);
}

void ilrd::ThreadPool::TPTask::Run() const
{
    m_task->Run();
}

ilrd::ThreadPool::PauseTask::PauseTask(): m_semaphore(0) {}

void ilrd::ThreadPool::PauseTask::Run()
{
    m_semaphore.release();
    std::unique_lock lock(m_mutex);
    m_condition.wait(lock);
}

void ilrd::ThreadPool::PauseTask::Notify()
{
    std::unique_lock lock(m_mutex);
    m_condition.notify_all();
}

void ilrd::ThreadPool::PauseTask::NotifyOne()
{
    std::unique_lock lock(m_mutex);
    m_condition.notify_one();
}

void ilrd::ThreadPool::PauseTask::Acquire()
{
    m_semaphore.acquire();
}

void ilrd::ThreadPool::RunThread()
{
    while(m_threadIsRunning)
    {
        TPTask task;
        m_taskQueue.Pop(task);
        task.Run();
    }

    m_toRemove.Push(std::this_thread::get_id());
}
