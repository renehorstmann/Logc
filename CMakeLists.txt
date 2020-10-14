cmake_minimum_required(VERSION 3.0)
project(Logc C)

set(CMAKE_C_STANDARD 11)
#set(CMAKE_CXX_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic -Wno-unused-function -Wno-missing-braces")

#add_definitions(-DLOGC_LEADING_TEXT="[CustomText] ")

include_directories(logc)

add_executable(example example.c)


add_library(log SHARED lib_example.c)


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/logc/log.py
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/lib_example.py
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
