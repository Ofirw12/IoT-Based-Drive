/*******************************************************************************
* FileName: ISchedulerTask                                                          *
 * Owner: Ofir Wijsboom                                                        *
 * Reviewer: TBD                                                     *
 * Review Status: pre-APPROVED (25/03/25)                                           *
 ******************************************************************************/

#ifndef ILRD_RD1645_ISCHEDULERTASK_HPP
#define ILRD_RD1645_ISCHEDULERTASK_HPP

namespace ilrd
{

class ISchedulerTask
{
public:
    virtual void Run() = 0;
    virtual ~ISchedulerTask() = default;

}; // class ISchedulerTask

} // namespace ilrd

#endif //ILRD_RD1645_ISCHEDULERTASK_HPP
