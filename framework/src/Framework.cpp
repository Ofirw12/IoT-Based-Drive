
#include "Framework.hpp"
#include "Factory.hpp"
#include "FW_TPTask.hpp"
#include "Handleton.hpp"
#include "ThreadPool.hpp"

using namespace ilrd;

Framework::Framework(
	const std::vector<std::pair<std::pair<int, FDMODE>, IInputProxy*>>& react_list,
	const std::vector<std::pair<int, std::function<ICommand*()>>>& factory_list,
	const std::string& plugins_dir)
		: m_dirMonitor(plugins_dir),
			m_reloadCB({m_dllLoader, &DllLoader::Reload}),
			m_deleteCB({m_dllLoader, &DllLoader::Unload})
{
	// factory init
	for (const auto& [key, creator] : factory_list)
	{
		Handleton::GetInstance<Factory<int, ICommand>>()->Register(key ,creator);
	}

	//reactor init
	for (const auto [pair, proxy] : react_list)
	{
		m_reactor.Register(pair.first, pair.second,
			[proxy](int fd, FDMODE mode)
			{
				std::shared_ptr<ITaskArgs> taskArgs = proxy->GetTaskArgs(fd, mode);
				if (taskArgs == nullptr)
				{
					return;
				}
				Handleton::GetInstance<ThreadPool>()->AddTask(std::make_shared<FW_TPTask>(taskArgs));
			});
	}

	// dll loader + monitor
	m_dirMonitor.RegisterForModify(&m_reloadCB);
	m_dirMonitor.RegisterForDelete(&m_deleteCB);
}

void Framework::Run()
{
	m_dirMonitor.Run();
	m_reactor.Run(); //blocking
}
