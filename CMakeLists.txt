cmake_minimum_required(VERSION 3.1)

project(CDR_db_test)

set(BOOST_COMPONENTS thread system program_options)
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Threads)

# specify the C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(project_src
    ${CMAKE_SOURCE_DIR}/main.cpp
    ${CMAKE_SOURCE_DIR}/cdr.h)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

add_executable(${PROJECT_NAME} ${project_src})

target_link_libraries(${PROJECT_NAME} ${PQXX_LIB} ${PQ_LIB})
target_link_libraries(${CMAKE_PROJECT_NAME}  ${CMAKE_THREAD_LIBS_INIT})
