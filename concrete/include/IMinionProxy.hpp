/*******************************************************************************
* FileName: IMinionProxy                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (06/04/2025)                                           *
 ******************************************************************************/
//
// Created by ofir on 4/6/25.
//

#ifndef ILRD_RD1645_IMINIONPROXY_HPP
#define ILRD_RD1645_IMINIONPROXY_HPP

#include <functional>
#include <memory>

#include "Ticket.hpp"
#include "AMessage.hpp"

namespace ilrd
{

class IMinionProxy
{
public:
	virtual ~IMinionProxy() = default;
	virtual void AddWriteTask(size_t offset, size_t length,
		std::shared_ptr<const char[]> data,
		std::function<void(const std::shared_ptr<TaskResult>&)> onDone,
		const UID& uid) = 0;
	virtual void AddReadTask(size_t offset, size_t length,
		std::function<void(const std::shared_ptr<TaskResult>&)> onDone,
		const UID& uid) = 0;
	virtual int GetMinionFD() = 0;
	virtual void OnMinionWakeup() = 0;

}; // class IMinionProxy

} // namespace ilrd

#endif //ILRD_RD1645_IMINIONPROXY_HPP
