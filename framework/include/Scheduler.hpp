/*******************************************************************************
* FileName: Scheduler                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (25/03/25)                                           *
 ******************************************************************************/

#ifndef ILRD_RD1645_SCHEDULER_HPP
#define ILRD_RD1645_SCHEDULER_HPP

#include <memory> // std::shared_ptr
#include <queue> // std::priority_queue
#include <condition_variable> // std::condition_variable

#include "Timer.hpp"
#include "ISchedulerTask.hpp"

namespace ilrd
{

class Scheduler
{
public:
    ~Scheduler();
    Scheduler(const Scheduler& other) = delete;
    Scheduler& operator=(const Scheduler& other) = delete;
    Scheduler& operator=(Scheduler&& other) = delete;
    Scheduler(Scheduler&& other) = delete;

    void AddTask(const std::shared_ptr<ISchedulerTask>& task,
                            std::chrono::milliseconds from_now);
private:
    friend class Handleton;
    class SchedulerTask;

    static void ThreadFunc(sigval sval);
    void HandleTask();
    Scheduler();
    std::priority_queue<SchedulerTask> m_queue;
    Timer m_timer;
    std::mutex m_mutex;
    std::condition_variable m_cv;

    class SchedulerTask
    {
    public:
        SchedulerTask(const std::shared_ptr<ISchedulerTask>& task,
                                    std::chrono::milliseconds ms);
        SchedulerTask(const SchedulerTask& other) = default;
        SchedulerTask(SchedulerTask&& other) = default;
        ~SchedulerTask() = default;
        SchedulerTask& operator=(SchedulerTask&& other) = default;
        SchedulerTask& operator=(const SchedulerTask& other) = delete;

        /// implements greater operator as if it was less operator,
        /// for priority_queue comparator
        bool operator<(const SchedulerTask& other) const;
        void Run() const;
        [[nodiscard]] std::chrono::time_point<std::chrono::system_clock>
                                                    GetTimePoint() const;
    private:
        std::shared_ptr<ISchedulerTask> m_task;
        std::chrono::time_point<std::chrono::system_clock> m_timeToRun;
    }; // class SchedulerTask
}; // class Scheduler


} // namespace ilrd

#endif //ILRD_RD1645_SCHEDULER_HPP
