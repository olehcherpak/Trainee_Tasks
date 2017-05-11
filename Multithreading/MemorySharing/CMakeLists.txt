cmake_minimum_required(VERSION 2.8)

project(MemorySharing)

set(LIB_NAME MemorySharing)
set(EXE_NAME runner)
set(SOURCE_EXE test.cpp)

add_compile_options(-Wall -std=c++11 -fpic)

set(SOURCE_LIB MemorySharing.cpp MemoryPart.cpp)


add_library(${LIB_NAME} SHARED ${SOURCE_LIB})



add_library(${LIB_NAME}_static STATIC ${SOURCE_LIB})


add_executable(${EXE_NAME} ${SOURCE_EXE})

target_link_libraries(${EXE_NAME} ${LIB_NAME} pthread)
