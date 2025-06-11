/*******************************************************************************
* FileName: WriteMessageResponse                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (09/04/2025)                                           *
 ******************************************************************************/
//
// Created by ofir on 4/9/25.
//

#ifndef ILRD_RD1645_WRITEMESSAGERESPONSE_HPP
#define ILRD_RD1645_WRITEMESSAGERESPONSE_HPP

#include "AMessage.hpp"

namespace ilrd
{

class WriteMessageResponse final : public AMessage
{
public:
	explicit WriteMessageResponse(const UID& uid, Result res);
	explicit WriteMessageResponse();
	~WriteMessageResponse() override = default;

	char* ToBuffer(char* buffer) override;
	char* FromBuffer(char* buffer) override;
	size_t GetSize() const override;
	uint32_t GetClassType() const override;

	Result GetResult() const;
private:
	Result m_res;


}; // class WriteMessageResponse

} // namespace ilrd

#endif //ILRD_RD1645_WRITEMESSAGERESPONSE_HPP
