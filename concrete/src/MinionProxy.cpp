

#include <cstring>
#include <iostream>

#include "MinionProxy.hpp"
#include "Factory.hpp"
#include "Handleton.hpp"
#include "Logger.hpp"
#include "ReadMessageResponse.hpp"
#include "ReadMessageSend.hpp"
#include "WriteMessageResponse.hpp"
#include "WriteMessageSend.hpp"


ilrd::MinionProxy::MinionProxy(const std::string& send_port, const std::string& to_ip)
	: m_socket(send_port, to_ip) {}

void ilrd::MinionProxy::AddReadTask(size_t offset, size_t length,
                                    std::function<void(const std::shared_ptr<TaskResult>&)> onDone, const UID& uid)
{
#ifndef NDEBUG
	std::cout << "AddReadTask:: offset: " << offset << " length: " << length << std::endl;
#endif
	std::shared_ptr<AMessage> msg = std::make_shared<ReadMessageSend>(uid, offset, length);
	std::vector<char> buffer(msg->GetSize());
	msg->ToBuffer(buffer.data());
	{
		std::unique_lock lock(m_mutex);
		m_OnDone.emplace(uid, onDone);
	}
	m_socket.Send(buffer);
}

void ilrd::MinionProxy::AddWriteTask(size_t offset, size_t length,
	std::shared_ptr<const char[]> data, std::function<void(const std::shared_ptr<TaskResult>&)> onDone, const UID& uid)
{
	std::shared_ptr<AMessage> msg = std::make_shared<WriteMessageSend>(uid, offset, length, data);

	std::vector<char> buffer(msg->GetSize());
	msg->ToBuffer(buffer.data());
	{
		std::unique_lock lock(m_mutex);
		m_OnDone.emplace(uid, onDone);
	}
	m_socket.Send(buffer);
#ifndef NDEBUG
	std::cout << "AddWriteTask:: offset: " << offset << " length: " << length << std::endl;
#endif

}

int ilrd::MinionProxy::GetMinionFD()
{
	return m_socket.GetSocket();
}

void ilrd::MinionProxy::OnMinionWakeup()
{
#ifndef NDEBUG
	std::cout << "MinionProxy::OnMinionWakeup" << std::endl;
#endif
	std::vector<char> data;
	data.resize(BUFSIZ);
	uint32_t size;
	m_socket.Recv(data);
	char* buffer = data.data();
	memcpy(&size, buffer, sizeof(uint32_t));
	buffer += sizeof(uint32_t);

	uint32_t type;
	memcpy(&type, buffer, sizeof(uint32_t));
	buffer += sizeof(uint32_t);

	std::shared_ptr<AMessage> msg = Handleton::GetInstance<Factory<int, AMessage>>()->Create(type);
	msg->FromBuffer(buffer);

	if (type == READ_RESPONSE)
	{
		auto resp = std::static_pointer_cast<ReadMessageResponse>(msg);
		auto data = std::shared_ptr<char[]>(new char[resp->GetLen()]);
		memcpy(data.get(), resp->GetData(), resp->GetLen());
		auto taskRes = std::make_shared<TaskResult>(resp->GetUID(), resp->GetResult(), data, resp->GetLen());
		std::unique_lock lock(m_mutex);
		m_OnDone[resp->GetUID()](taskRes);
	}
	else if (type == WRITE_RESPONSE)
	{
		auto resp = std::static_pointer_cast<WriteMessageResponse>(msg);
		auto taskRes = std::make_shared<TaskResult>(resp->GetUID(), resp->GetResult(), nullptr, 0);
		std::unique_lock lock(m_mutex);
		m_OnDone[resp->GetUID()](taskRes);
	}
}
