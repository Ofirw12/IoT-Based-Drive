/*******************************************************************************
* FileName: MinionCommandWrite                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (20/04/2025)                                           *
 ******************************************************************************/
//
// Created by ofir on 4/20/25.
//

#ifndef ILRD_RD1645_MINIONCOMMANDWRITE_HPP
#define ILRD_RD1645_MINIONCOMMANDWRITE_HPP

#include "ICommand.hpp"
namespace ilrd
{

class MinionCommandWrite final : public ICommand
{
public:
	std::optional<std::pair<std::function<bool()>,
		std::chrono::milliseconds>> Run(std::shared_ptr<ITaskArgs> taskArgs) override;
}; // class MinionCommandWrite

} // namespace ilrd

#endif //ILRD_RD1645_MINIONCOMMANDWRITE_HPP
