cmake_minimum_required(VERSION 3.20)

project(waitable_queue)
add_executable(waitable_queue TestWaitableQueue.cpp)

project(thread_pool)
add_executable(thread_pool TestThreadPool.cpp)
target_link_libraries(thread_pool thread_pool_static)

project(factory)
add_executable(factory TestFactory.cpp)

project(singleton)
add_executable(singleton TestSingleton.cpp)

project(handleton)
add_executable(handleton TestHandleton.cpp)
target_link_libraries(handleton handleton_shared)
add_library(handleton_dll1 SHARED TestHandletondll1.cpp)
target_link_libraries(handleton_dll1 handleton_shared)
add_library(handleton_dll2 SHARED TestHandletondll2.cpp)
target_link_libraries(handleton_dll2 handleton_shared)

project(logger)
add_executable(logger TestLogger.cpp)
target_link_libraries(logger logger_shared handleton_shared)

project(dispatcher)
add_executable(dispatcher TestDispatcher.cpp)

add_executable(dirmonitor TestDirMonitor.cpp)
target_link_libraries(dirmonitor dirmonitor_shared)

add_library(dllplugin SHARED TestDllLoader.cpp)
target_link_libraries(dllplugin handleton_shared)

add_executable(reactor TestReactor.cpp)
target_link_libraries(reactor reactor_static udpsocket tcpclient tcpclient)

add_executable(scheduler_cpp TestScheduler.cpp)
target_link_libraries(scheduler_cpp scheduler_cpp_static)

add_executable(async_inject TestAsyncInjection.cpp)
target_link_libraries(async_inject async_inject_static)

add_executable(master TestMaster.cpp)
target_link_libraries(master framework_static nbdproxy_static tcpserver)