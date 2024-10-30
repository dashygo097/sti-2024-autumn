# build
cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 17)
project (demo)

# src inc include
set(SOURCES src/main.c src/signals.c src/FO.c src/judge.c)
add_executable(demo ${SOURCES})
target_include_directories(demo PUBLIC ${PROJECT_SOURCE_DIR}/inc ${PROJECT_SOURCE_DIR}/include)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

if(CMAKE_SYSTEM_NAME MATCHES "Linux")

elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fexec-charset=GBK")#Windows 编码问题
endif()

# debug

message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message("PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")

message("SOURCES: ${SOURCES}")
