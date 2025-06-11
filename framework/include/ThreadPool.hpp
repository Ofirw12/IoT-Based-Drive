
#ifndef ILRD_R1645_THREADPOOL_HPP
#define ILRD_R1645_THREADPOOL_HPP

#include <map> // std::map
#include <thread> // std::jthread

#include "ITPTask.hpp"
#include "WaitableQueue.hpp"

namespace ilrd
{

class ThreadPool
{
public:
    enum Priority
    {
        LOW = 1,
        MEDIUM = 2,
        HIGH = 3,
    };

    ~ThreadPool();
    void AddTask(const std::shared_ptr<threadpool::ITPTask>&,
                                    Priority priority = LOW);
    void SetNumThreads(size_t numThreads);
    void Pause();
    void Resume();

private:
    explicit ThreadPool(size_t numThreads =
                std::thread::hardware_concurrency() != 1 ?
                    std::thread::hardware_concurrency() - 1 : 1);
    void RunThread();

    friend class Handleton;
    class PauseTask;
    class TPTask;

    WaitableQueue<TPTask, std::priority_queue<TPTask>> m_taskQueue;
    WaitableQueue<std::thread::id> m_toRemove;
    std::map<std::thread::id, std::unique_ptr<std::jthread>> m_threads;
    std::shared_ptr<PauseTask> m_pauseTask;
    static thread_local bool m_threadIsRunning;
    static const std::shared_ptr<threadpool::ITPTask> m_setOffFunc;
    bool m_isRunning;

    class TPTask
    {
    public:
        explicit TPTask(const std::shared_ptr<threadpool::ITPTask>& task = nullptr,
                                                unsigned int priority = 1);
        bool operator<(const TPTask& other) const;
        void Run() const;
    private:
        std::shared_ptr<threadpool::ITPTask> m_task;
        unsigned int m_priority;
        std::chrono::time_point<std::chrono::steady_clock> m_start;
    }; // class TPTask

    class PauseTask final : public threadpool::ITPTask
    {
    public:
        PauseTask();
        void Run() override;
        void Notify();
        void NotifyOne();
        void Acquire();
    private:
        std::mutex m_mutex;
        std::condition_variable m_condition;
        std::counting_semaphore<> m_semaphore;
    }; // class PauseTask

}; //class ThreadPool
}// namespace ilrd

#endif //ILRD_R1645_THREADPOOL_HPP
