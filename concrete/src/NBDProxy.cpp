#include <iostream>

#include "NBDProxy.hpp"

#include <cstring>
#include <netinet/in.h>

#include "Factory.hpp"
#include "Handleton.hpp"
#include "NBDReadArgs.hpp"
#include "NBDWriteArgs.hpp"
using namespace ilrd;


NBDArgs::NBDArgs(size_t offset,	size_t len, const std::shared_ptr<char[]>& buffer)
	: m_offset(offset) , m_len(len), m_buffer(buffer)
{}

NBDProxy::NBDProxy(Nbd& nbd) : m_nbd(nbd)
{
	Handleton::GetInstance<Factory<NBDArgType, ATaskArgs, NBDArgs>>()->Register(
		AREAD, [](const NBDArgs& data)
		{
			return new NBDReadArgs(data);
		});
	Handleton::GetInstance<Factory<NBDArgType, ATaskArgs, NBDArgs>>()->Register(
		AWRITE, [](const NBDArgs& data)
		{
			return new NBDWriteArgs(data);
		});
}

std::shared_ptr<ITaskArgs> NBDProxy::GetTaskArgs(int fd, FDMODE mode)
{
	std::vector<char> buffer(sizeof(nbd_request));
	std::unique_lock lock(m_mutex);
		m_nbd.GetTcpSocket().Recv(buffer);
	lock.unlock();
	const auto nbd_req = *reinterpret_cast<nbd_request*>(buffer.data());
	uint32_t len = ntohl(nbd_req.len);
	uint32_t offset = Nbd::Ntohll(nbd_req.from);

	if (nbd_req.magic != ntohl(NBD_REQUEST_MAGIC))
	{
		throw std::runtime_error("NBD request magic mismatch");
	}

	std::shared_ptr<ATaskArgs> atask = nullptr;
	NBDArgs args(offset, len, nullptr);
	switch (ntohl(nbd_req.type))
	{
	case NBD_CMD_READ:
		atask = Handleton::GetInstance<Factory<NBDArgType, ATaskArgs, NBDArgs>>()->Create(AREAD, args);
		break;
	case NBD_CMD_WRITE:
	{
		args.m_buffer = std::make_shared<char[]>(len);
		std::vector<char> buff(len);
		lock.lock();
			m_nbd.GetTcpSocket().Recv(buff);
		lock.unlock();
		memcpy(args.m_buffer.get(), buff.data(), len);
		atask = Handleton::GetInstance<Factory<NBDArgType, ATaskArgs, NBDArgs>>()->Create(AWRITE, args);

		break;
	}
	default:
		throw std::runtime_error("NBD request type not supported");
	}

	lock.lock();
		nbd_reply& reply = m_replies.emplace(atask->GetUID(), nbd_reply{}).first->second;
		reply.magic = ntohl(NBD_REPLY_MAGIC);
		reply.error = Nbd::Ntohll(0);
		memcpy(reply.handle, nbd_req.handle, sizeof(nbd_req.handle));
	lock.unlock();

	m_dispatcher.Notify(atask);
	return atask;
}

void NBDProxy::RegisterForNewTaskArgs(ACallback<const std::shared_ptr<ATaskArgs>&>* callback)
{
	m_dispatcher.Register(callback);
}

void NBDProxy::NBDSendResponse(const TaskResult& taskRes)
{
	std::unique_lock lock(m_mutex);
		const auto rep = m_replies[taskRes.m_uid];
		m_replies.erase(taskRes.m_uid);
	lock.unlock();

	std::vector<char> toSend(sizeof(nbd_reply));
	*reinterpret_cast<nbd_reply*>(toSend.data()) = rep;
	lock.lock();
	m_nbd.GetTcpSocket().Send(toSend);

	if (taskRes.m_data != nullptr)
	{
		const std::vector buffer(taskRes.m_data.get(), taskRes.m_data.get() + taskRes.m_len);
		m_nbd.GetTcpSocket().Send(buffer);
	}

}

