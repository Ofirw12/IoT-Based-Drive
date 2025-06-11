/*******************************************************************************
* FileName: ATaskArgs                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (06/04/2025)                                           *
 ******************************************************************************/
//
// Created by ofir on 4/6/25.
//

#ifndef ILRD_RD1645_ATASKARGS_HPP
#define ILRD_RD1645_ATASKARGS_HPP

#include <memory>
#include <linux/nbd.h>

#include "ITaskArgs.hpp"
#include "UID.hpp"

namespace ilrd
{

enum NBDArgType
{
	AREAD = 0,
	AWRITE = 1
};

struct NBDArgs
{
	NBDArgs(size_t offset, size_t len,
		const std::shared_ptr<char[]>& buffer = nullptr);
	size_t m_offset;
	size_t m_len;
	std::shared_ptr<char[]> m_buffer;
};

class ATaskArgs : public ITaskArgs
{
public:
	explicit ATaskArgs();
    virtual UID GetUID();
private:
	UID m_uid;
}; // class ATaskArgs

} // namespace ilrd

#endif //ILRD_RD1645_ATASKARGS_HPP
