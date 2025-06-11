cmake_minimum_required(VERSION 3.20)


target_sources(nbdproxy_static PRIVATE AMessage.hpp ATaskArgs.hpp MasterCommandWrite.hpp MasterCommandRead.hpp IMinionProxy.hpp IResponse.hpp MinionManager.hpp MinionProxy.hpp NBDWriteArgs.hpp NBDReadArgs.hpp NBDProxy.hpp WriteResponse.hpp ReadResponse.hpp ResponseManager.hpp Ticket.hpp UID.hpp)
target_sources(nbdproxy_shared PRIVATE AMessage.hpp ATaskArgs.hpp MasterCommandWrite.hpp MasterCommandRead.hpp IMinionProxy.hpp IResponse.hpp MinionManager.hpp MinionProxy.hpp NBDWriteArgs.hpp NBDReadArgs.hpp NBDProxy.hpp WriteResponse.hpp ReadResponse.hpp ResponseManager.hpp Ticket.hpp UID.hpp)

target_sources(messages_static PRIVATE AMessage.hpp WriteMessageSend.hpp WriteMessageResponse.hpp ReadMessageResponse.hpp ReadMessageSend.hpp)
target_sources(messages_shared PRIVATE AMessage.hpp WriteMessageSend.hpp WriteMessageResponse.hpp ReadMessageResponse.hpp ReadMessageSend.hpp)
