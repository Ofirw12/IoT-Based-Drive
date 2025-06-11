
#ifndef ILRD_RD1645_FRAMEWORK_HPP
#define ILRD_RD1645_FRAMEWORK_HPP

#include <functional>
#include <string>

#include "DirMonitor.hpp"
#include "DllLoader.hpp"
#include "ICommand.hpp"
#include "IInputProxy.hpp"
#include "Reactor.hpp"

namespace ilrd
{

class Framework
{
public:
	explicit Framework(const std::vector<std::pair<std::pair<int, FDMODE>, IInputProxy*>>& react_list,
						const std::vector<std::pair<int, std::function<ICommand*()>>>& factory_list,
						const std::string& plugins_dir = "./plugins");
	void Run();

private:
	DirMonitor m_dirMonitor;
	DllLoader m_dllLoader;
	Reactor m_reactor;
	Callback<const std::string&, DllLoader> m_reloadCB;
	Callback<const std::string&, DllLoader> m_deleteCB;

}; // class Framework

} // namespace ilrd

#endif //ILRD_RD1645_FRAMEWORK_HPP
