cmake_minimum_required(VERSION 3.20)

#project(framework)
#add_library(framework_static STATIC Framework.cpp FW_TPTask.cpp)
#add_library(framework_shared SHARED Framework.cpp FW_TPTask.cpp)
#target_link_libraries(framework_static dirmonitor_static reactor_static async_inject_static thread_pool_static logger_static)
#target_link_libraries(framework_shared dirmonitor_shared reactor_shared async_inject_shared thread_pool_shared logger_shared)

add_library(messages_static STATIC AMessage.cpp WriteMessageResponse.cpp WriteMessageSend.cpp ReadMessageResponse.cpp ReadMessageSend.cpp)
add_library(messages_shared SHARED AMessage.cpp WriteMessageResponse.cpp WriteMessageSend.cpp ReadMessageResponse.cpp ReadMessageSend.cpp)

add_library(uid_static STATIC UID.cpp)
add_library(uid_shared SHARED UID.cpp)

add_library(nbd_static STATIC NBD.cpp)
add_library(nbd_shared SHARED NBD.cpp)

project(nbdproxy)
add_library(nbdproxy_static STATIC NBDProxy.cpp MasterCommandRead.cpp MasterCommandWrite.cpp ATaskArgs.cpp NBDReadArgs.cpp NBDWriteArgs.cpp MinionManager.cpp MinionProxy.cpp UID.cpp ResponseManager.cpp Ticket.cpp WriteResponse.cpp ReadResponse.cpp)
add_library(nbdproxy_shared SHARED NBDProxy.cpp MasterCommandRead.cpp MasterCommandWrite.cpp ATaskArgs.cpp NBDReadArgs.cpp NBDWriteArgs.cpp MinionManager.cpp MinionProxy.cpp UID.cpp ResponseManager.cpp Ticket.cpp WriteResponse.cpp ReadResponse.cpp)
target_link_libraries(nbdproxy_static udpsocket messages_static uid_static nbd_static)
target_link_libraries(nbdproxy_shared udpsocket messages_shared uid_shared nbd_shared)

project(minion)
add_library(minion_static STATIC MasterProxy.cpp FileManager.cpp MinionCommandRead.cpp MinionCommandWrite.cpp MinionReadArgs.cpp MinionWriteArgs.cpp)
add_library(minion_shared SHARED MasterProxy.cpp FileManager.cpp MinionCommandRead.cpp MinionCommandWrite.cpp MinionReadArgs.cpp MinionWriteArgs.cpp)
target_link_libraries(minion_static udpsocket messages_static uid_static framework_static)
target_link_libraries(minion_shared udpsocket messages_shared uid_shared framework_shared)
