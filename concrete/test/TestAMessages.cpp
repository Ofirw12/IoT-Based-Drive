
#include <iostream>

#include "ReadMessageResponse.hpp"
#include "ReadMessageSend.hpp"
#include "WriteMessageResponse.hpp"
#include "WriteMessageSend.hpp"

void TestReadMessageSend()
{
	std::cout << "TestReadMessageSend" << std::endl;
	ilrd::ReadMessageSend readMessageSend(ilrd::UID(), 4, 6);
	auto sendBuff = new char[readMessageSend.GetSize()]{};
	readMessageSend.ToBuffer(sendBuff);
	ilrd::ReadMessageSend readMessageRecieved;
	char* runner = sendBuff;
	runner += 2*sizeof(uint32_t);

	readMessageRecieved.FromBuffer(runner);
	std::cout << readMessageRecieved.GetOffset() << readMessageRecieved.GetLength() << std::endl;
	delete[] sendBuff;
}

void TestWriteMessageSend()
{
	std::cout << "TestWriteMessageSend" << std::endl;
	const auto data = std::shared_ptr<const char[]>(new const char[8]{"bla bla"});
	ilrd::WriteMessageSend writeMessageSend(ilrd::UID(), 4, 7, data);
	const auto sendBuff = new char[writeMessageSend.GetSize()];
	writeMessageSend.ToBuffer(sendBuff);
	char* runner = sendBuff;
	runner += 2*sizeof(uint32_t);

	ilrd::WriteMessageSend writeMessageRecieved;
	writeMessageRecieved.FromBuffer(runner);
	std::cout << writeMessageRecieved.GetOffset() << " " <<writeMessageRecieved.GetLength() << std::endl;
	std::cout << writeMessageRecieved.GetData() << std::endl;
	delete[] sendBuff;
}

void TestWriteMessageResponse()
{
	std::cout << "TestWriteMessageResponse" << std::endl;
	auto data = std::shared_ptr<const char[]>(new const char[8]{"bla bla"});
	ilrd::WriteMessageResponse writeMessageResp(ilrd::UID(), ilrd::SUCCESS);
	const auto sendBuff = new char[writeMessageResp.GetSize()];
	writeMessageResp.ToBuffer(sendBuff);
	ilrd::WriteMessageResponse writeMessageResponse;
	char* runner = sendBuff;
	runner += 2*sizeof(uint32_t);

	writeMessageResponse.FromBuffer(runner);
	std::cout << writeMessageResponse.GetResult() << std::endl;
	delete[] sendBuff;
}

void TestReadMessageResponse()
{
	std::cout << "TestReadMessageResponse" << std::endl;
	auto data = std::shared_ptr<const char[]>(new const char[8]{"bla bla"});
	ilrd::ReadMessageResponse readMessageResp(ilrd::UID(), data, ilrd::SUCCESS);
	auto sendBuff = new char[readMessageResp.GetSize()];
	readMessageResp.ToBuffer(sendBuff);
	ilrd::ReadMessageResponse readMessageRecieved;
	char* runner = sendBuff;
	runner += 2*sizeof(uint32_t);

	readMessageRecieved.FromBuffer(runner);
	std::cout << readMessageRecieved.GetLen() << std::endl;
	std::cout << readMessageRecieved.GetData() << std::endl;
	delete[] sendBuff;
}

int main()
{
	TestReadMessageSend();
	TestWriteMessageSend();
	TestReadMessageResponse();
	TestWriteMessageResponse();
	return 0;
}