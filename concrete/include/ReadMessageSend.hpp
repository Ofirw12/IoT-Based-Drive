/*******************************************************************************
* FileName: ReadMessageSend                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (09/04/2025)                                           *
 ******************************************************************************/
//
// Created by ofir on 4/9/25.
//

#ifndef ILRD_RD1645_READMESSAGESEND_HPP
#define ILRD_RD1645_READMESSAGESEND_HPP
#include "AMessage.hpp"

namespace ilrd
{

class ReadMessageSend final : public AMessage
{
public:
	explicit ReadMessageSend(const UID& uid, size_t offset, size_t len);
	explicit ReadMessageSend();
	~ReadMessageSend() override = default;

	char* ToBuffer(char* buffer) override;
	char* FromBuffer(char* buffer) override;
	size_t GetSize() const override;
	uint32_t GetClassType() const override;

	size_t GetOffset() const;
	size_t GetLength() const;
private:
	uint32_t m_offset;
	uint32_t m_len;
}; // class ReadMessageSend

} // namespace ilrd

#endif //ILRD_RD1645_READMESSAGESEND_HPP
