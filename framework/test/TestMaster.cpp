
#include "Framework.hpp"
#include "Handleton.hpp"
#include "IMinionProxy.hpp"
#include "MasterCommandRead.hpp"
#include "MasterCommandWrite.hpp"
#include "MinionManager.hpp"
#include "MinionProxy.hpp"
#include "NBDProxy.hpp"
#include "ResponseManager.hpp"

ilrd::ICommand* CreateReadCommand()
{
	return new ilrd::MasterCommandRead;
}

ilrd::ICommand* CreateWriteCommand()
{
	return new ilrd::MasterCommandWrite;
}

void TestMaster()
{
	std::vector<std::shared_ptr<ilrd::IMinionProxy>> minions;

	minions.push_back(std::make_shared<ilrd::MinionProxy>("8080","127.0.0.1"));
	minions.push_back(std::make_shared<ilrd::MinionProxy>("8081","10.1.0.49"));
	minions.push_back(std::make_shared<ilrd::MinionProxy>("8082","10.1.0.130"));
	constexpr size_t devSize = 3 * 4 * 1024 * 1024;


	ilrd::Handleton::GetInstance<ilrd::MinionManager>()->Init(devSize, minions);
	auto nbd = ilrd::Nbd("/dev/nbd0");
	ilrd::NBDProxy nbdProxy(nbd);
	ilrd::Handleton::GetInstance<ilrd::ResponseManager>()->Init(&nbdProxy);
	const std::vector<std::pair<std::pair<int, ilrd::FDMODE>, ilrd::IInputProxy*>> input_proxies =
		{
		{{nbd.GetTcpSocket().GetSocket(), ilrd::READ}, &nbdProxy}
		};
	const std::vector<std::pair<int, std::function<ilrd::ICommand*()>>> creators =
		{
		{ilrd::READ, &CreateReadCommand},
		{ilrd::WRITE, &CreateWriteCommand}
		};
	ilrd::Framework fw(input_proxies, creators, "./plugins");
	fw.Run();
}

int main()
{
	TestMaster();
}