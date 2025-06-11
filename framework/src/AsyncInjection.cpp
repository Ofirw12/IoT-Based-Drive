
#include "AsyncInjection.hpp"
#include "Handleton.hpp"

#include <memory> // std::shared_ptr

using namespace ilrd;

AsyncInjection::AsyncInjection(const std::function<bool()>& func, std::chrono::milliseconds interval)
: m_interval(interval), m_func(func), m_task(std::make_shared<AsyncInjectionTask>(*this))
{
	Handleton::GetInstance<Scheduler>()->AddTask(m_task, m_interval);
}

AsyncInjection::AsyncInjectionTask::AsyncInjectionTask(AsyncInjection& ai)
	: m_ai(ai) {}

void AsyncInjection::AsyncInjectionTask::Run()
{
	m_ai.PerformAction();
}

void AsyncInjection::PerformAction() const
{
	if (!m_func())
	{
		Handleton::GetInstance<Scheduler>()->AddTask(m_task, m_interval);
	}
	else
	{
		delete this;
	}
}

