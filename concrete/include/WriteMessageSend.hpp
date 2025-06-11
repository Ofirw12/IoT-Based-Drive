
#ifndef ILRD_RD1645_WRITEMESSAGESEND_HPP
#define ILRD_RD1645_WRITEMESSAGESEND_HPP

#include "AMessage.hpp"

namespace ilrd
{

class WriteMessageSend final : public AMessage
{
public:
	explicit WriteMessageSend(const UID& uid, size_t offset, size_t len, std::shared_ptr<const char[]> data);
	explicit WriteMessageSend();
	~WriteMessageSend() override;

	char* ToBuffer(char* buffer) override;
	char* FromBuffer(char* buffer) override;
	size_t GetSize() const override;
	uint32_t GetClassType() const override;

	size_t GetOffset() const;
	size_t GetLength() const;
	char* GetData() const;

private:
	static char* AllocAndCpy(std::shared_ptr<const char[]> data, size_t len);
    uint32_t m_offset;
	uint32_t m_len;
	char* m_data;

}; // class AMessageResponse

} // namespace ilrd

#endif //ILRD_RD1645_WRITEMESSAGESEND_HPP
