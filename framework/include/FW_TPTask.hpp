/*******************************************************************************
* FileName: FW_TPTask                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: Gil Fridman					                                   *
 * Review Status: APPROVED (30/03/2025)                                        *
 ******************************************************************************/

#ifndef ILRD_RD1645_FW_TPTASK_HPP
#define ILRD_RD1645_FW_TPTASK_HPP

#include <memory>

#include "ITPTask.hpp"
#include "ITaskArgs.hpp"

namespace ilrd
{

class FW_TPTask final : public threadpool::ITPTask
{
public:
	explicit FW_TPTask(const std::shared_ptr<ITaskArgs>& args);
    void Run() override;
private:
	std::shared_ptr<ITaskArgs> m_taskArgs;
}; // class FW_TPTask

} // namespace ilrd

#endif //ILRD_RD1645_FW_TPTASK_HPP
