cmake_minimum_required(VERSION 3.16)
project(ultimate-bogo)

set(CMAKE_CXX_STANDARD 20)

add_executable(ultimate-bogo main.cpp Bogo.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)