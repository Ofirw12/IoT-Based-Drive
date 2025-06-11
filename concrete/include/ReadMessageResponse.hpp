
#ifndef ILRD_RD1645_READMESSAGERESPONSE_HPP
#define ILRD_RD1645_READMESSAGERESPONSE_HPP

#include "AMessage.hpp"

namespace ilrd
{

class ReadMessageResponse final : public AMessage
{
public:
	explicit ReadMessageResponse();
	explicit ReadMessageResponse(const UID& uid,
		std::shared_ptr<const char[]> data, size_t len, Result res);
	~ReadMessageResponse() override;

	char* ToBuffer(char* buffer) override;
	char* FromBuffer(char* buffer) override;
	size_t GetSize() const override;
	uint32_t GetClassType() const override;

    Result GetResult() const;
	char* GetData() const;
	size_t GetLen() const;
private:
	static char* AllocAndCpy(std::shared_ptr<const char[]> data, size_t len);
	uint32_t m_len;
	char* m_data;
    Result m_res;
}; // class ReadMessageResponse

} // namespace ilrd

#endif //ILRD_RD1645_READMESSAGERESPONSE_HPP
