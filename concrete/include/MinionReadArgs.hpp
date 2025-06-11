/*******************************************************************************
* FileName: MinionReadArgs                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (20/04/2025)                                           *
 ******************************************************************************/
//
// Created by ofir on 4/20/25.
//

#ifndef ILRD_RD1645_MINIONREADARGS_HPP
#define ILRD_RD1645_MINIONREADARGS_HPP
#include <memory>

#include "ITaskArgs.hpp"
#include "UID.hpp"

namespace ilrd
{

class MinionReadArgs final : public ITaskArgs
{
public:
	explicit MinionReadArgs(size_t offset, size_t len, std::shared_ptr<char[]> data, UID uid);
	size_t GetOffset() const;
	size_t GetLen() const;
	std::shared_ptr<char[]> GetData();
	UID GetUID();
	int GetKey() override;
private:
	size_t m_offset;
	size_t m_len;
	std::shared_ptr<char[]> m_data;
	UID m_uid;
}; // class MinionReadArgs

} // namespace ilrd

#endif //ILRD_RD1645_MINIONREADARGS_HPP
