cmake_minimum_required(VERSION 3.20)
project(final_project)

project(waitable_queue)

project(thread_pool)
add_library(thread_pool_static STATIC ThreadPool.cpp)
add_library(thread_pool_shared SHARED ThreadPool.cpp)

project(handleton)
add_library(handleton_shared SHARED Handleton.cpp)

project(logger)
add_library(logger_static STATIC Logger.cpp)
add_library(logger_shared SHARED Logger.cpp)

project(dirmonitor)
add_library(dirmonitor_static STATIC DirMonitor.cpp DllLoader.cpp)
add_library(dirmonitor_shared SHARED DirMonitor.cpp DllLoader.cpp)

project(reactor)
add_library(reactor_static STATIC Reactor.cpp IListener.cpp)
add_library(reactor_shared SHARED Reactor.cpp IListener.cpp)

project(scheduler_cpp)
add_library(scheduler_cpp_static STATIC Scheduler.cpp Timer.cpp)
add_library(scheduler_cpp_shared SHARED Scheduler.cpp Timer.cpp)
target_link_libraries(scheduler_cpp_static handleton_shared)
target_link_libraries(scheduler_cpp_shared handleton_shared)

project(async_inject)
add_library(async_inject_static STATIC AsyncInjection.cpp)
add_library(async_inject_shared SHARED AsyncInjection.cpp)
target_link_libraries(async_inject_static scheduler_cpp_static)
target_link_libraries(async_inject_shared scheduler_cpp_shared)

add_library(udpsocket STATIC UDPSocket.cpp)
add_library(tcpclient STATIC TCPSocket.cpp TCPClient.cpp)
add_library(tcpserver STATIC TCPSocket.cpp TCPServer.cpp TCPConnection.cpp)

project(framework)
add_library(framework_static STATIC Framework.cpp FW_TPTask.cpp)
add_library(framework_shared SHARED Framework.cpp FW_TPTask.cpp)
target_link_libraries(framework_static dirmonitor_static reactor_static async_inject_static thread_pool_static logger_static)
target_link_libraries(framework_shared dirmonitor_shared reactor_shared async_inject_shared thread_pool_shared logger_shared)


