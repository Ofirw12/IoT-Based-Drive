
#ifndef ILRD_RD1645_ASYNCINJECTION_HPP
#define ILRD_RD1645_ASYNCINJECTION_HPP

#include <functional> // std::function

#include "ISchedulerTask.hpp"
#include "Scheduler.hpp"

namespace ilrd
{

class AsyncInjection
{
public:
    AsyncInjection(const std::function<bool()>& func, std::chrono::milliseconds interval);
private:
	~AsyncInjection() = default;
	class AsyncInjectionTask final : public ISchedulerTask
	{
	public:
		explicit AsyncInjectionTask(AsyncInjection& ai);
		void Run() override;
	private:
		AsyncInjection& m_ai;
	};
	/// runs the m_internal task, if return value is true,
	/// the AsyncInjection is getting deleted,
	/// otherwise it gets reinserted into the scheduler
	void PerformAction() const;

	std::chrono::milliseconds m_interval;
	std::function<bool()> m_func;
	std::shared_ptr<ISchedulerTask> m_task;
}; // class AsyncInjection

} // namespace ilrd

#endif //ILRD_RD1645_ASYNCINJECTION_HPP
