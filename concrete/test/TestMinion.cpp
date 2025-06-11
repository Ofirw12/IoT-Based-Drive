
#include <cassert>

#include "Framework.hpp"
#include "Handleton.hpp"
#include "MasterProxy.hpp"
#include "MinionCommandRead.hpp"
#include "MinionCommandWrite.hpp"

using namespace ilrd;

int main(int argc, char** argv)
{
	assert(argc > 1);
	Handleton::GetInstance<MasterProxy>()->Init(argv[1]);
	int fd = Handleton::GetInstance<MasterProxy>()->GetSocketFD();
	const std::vector<std::pair<std::pair<int, FDMODE>, IInputProxy*>> react_list =
		{
		{{fd, READ}, Handleton::GetInstance<MasterProxy>()}
		};
	const std::vector<std::pair<int, std::function<ICommand*()>>>& factory_list =
		{
		{READ, []{return new MinionCommandRead();}},
		{WRITE, []{return new MinionCommandWrite();}}
		};
	Framework fw(react_list,factory_list, "./plugins");
	fw.Run();
}
