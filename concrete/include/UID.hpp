/*******************************************************************************
* FileName: UID                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (07/04/2025)                                           *
 ******************************************************************************/
//
// Created by ofir on 4/7/25.
//

#ifndef ILRD_RD1645_UID_HPP
#define ILRD_RD1645_UID_HPP

#include <cstddef> //size_t

namespace ilrd
{

class UID
{
public:
    UID();
	UID(size_t num);
	UID(const UID& other);
	bool operator<(const UID& other) const;
	size_t GetUID() const;
private:
	static size_t m_counter;
	size_t m_uid;
}; // class UID

} // namespace ilrd

#endif //ILRD_RD1645_UID_HPP
