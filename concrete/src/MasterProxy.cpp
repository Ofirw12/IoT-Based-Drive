
#include <cstring>

#include "MasterProxy.hpp"

#include <iostream>

#include "MinionReadArgs.hpp"
#include "MinionWriteArgs.hpp"
#include "ReadMessageResponse.hpp"
#include "ReadMessageSend.hpp"
#include "WriteMessageResponse.hpp"
#include "WriteMessageSend.hpp"

std::shared_ptr<ilrd::ITaskArgs> ilrd::MasterProxy::GetTaskArgs(int fd,
                                                                FDMODE mode)
{
	std::vector<char> read(BUFSIZ);
	uint32_t size;
	m_socket.value().Recv(read);
	auto buffer = read.data();
	memcpy(&size, buffer, sizeof(uint32_t));
	buffer += sizeof(uint32_t);
	uint32_t type;
	memcpy(&type, buffer, sizeof(uint32_t));
	buffer += sizeof(uint32_t);

	std::shared_ptr<ITaskArgs> args = nullptr;
	if (type == READ_SEND)
	{
		ReadMessageSend msg;
		msg.FromBuffer(buffer);
		auto to = std::shared_ptr<char[]>(new char[msg.GetLength()]);
		args = std::make_shared<MinionReadArgs>(msg.GetOffset(), msg.GetLength(), to, msg.GetUID());
	}
	else
	{
		WriteMessageSend msg;
		msg.FromBuffer(buffer);
		auto from = std::shared_ptr<char[]>(new char[msg.GetLength()]);
		memcpy(from.get(), msg.GetData(), msg.GetLength());
		args = std::make_shared<MinionWriteArgs>(msg.GetOffset(), msg.GetLength(), from, msg.GetUID());
	}
	return args;
}

void ilrd::MasterProxy::Init(const std::string& port)
{
	m_socket.emplace(port);
}

int ilrd::MasterProxy::GetSocketFD() const
{
	return m_socket.value().GetSocket();
}

void ilrd::MasterProxy::SendReadResponse(bool status, std::shared_ptr<char[]> data, size_t len, UID uid)
{
	const Result res = status ? SUCCESS : FAILURE;
	auto resp = ReadMessageResponse(uid, data, len, res);
	std::vector<char> buffer(resp.GetSize());
	resp.ToBuffer(buffer.data());
	m_socket.value().Send(buffer);
}

void ilrd::MasterProxy::SendWriteResponse(bool status, UID uid)
{
	const Result res = status ? SUCCESS : FAILURE;
	auto resp = WriteMessageResponse(uid, res);
	std::vector<char> buffer(resp.GetSize());
	resp.ToBuffer(buffer.data());
	m_socket.value().Send(buffer);
}
