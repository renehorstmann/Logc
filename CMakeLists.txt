cmake_minimum_required(VERSION 3.0)
project(Logc C)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic -Wno-unused-function -Wno-missing-braces")

#add_definitions(-DLOGC_LEADING_TEXT="[CustomText] ")

include_directories(logc)

add_executable(example example.c logc/log.c)
