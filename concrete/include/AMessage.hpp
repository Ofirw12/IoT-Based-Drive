/*******************************************************************************
* FileName: AMessage                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (06/04/2025)                                           *
 ******************************************************************************/
//
// Created by ofir on 4/6/25.
//

#ifndef ILRD_RD1645_AMESSAGE_HPP
#define ILRD_RD1645_AMESSAGE_HPP

#include <memory>

#include "UID.hpp"

namespace ilrd
{

enum Result
{
	SUCCESS = 0,
	FAILURE = 1
};

enum CLASS_TYPE
{
	WRITE_SEND = 0,
	READ_SEND = 1,
	WRITE_RESPONSE = 2,
	READ_RESPONSE = 3
};

class AMessage
{
public:
	explicit AMessage(const UID& uid);
	virtual ~AMessage() = default;

	virtual char* ToBuffer(char* buffer);
	virtual char* FromBuffer(char* buffer) = 0;
	virtual size_t GetSize() const = 0;
	virtual uint32_t GetClassType() const = 0;

    UID GetUID();

private:
	UID m_uid;

}; // class AMessage

} // namespace ilrd

#endif //ILRD_RD1645_AMESSAGE_HPP
