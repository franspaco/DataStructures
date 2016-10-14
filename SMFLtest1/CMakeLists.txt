cmake_minimum_required(VERSION 3.6)
project(SMFLtest1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Rectangle.cpp Rectangle.h LinkedList.h Node.h)
add_executable(SMFLtest1 ${SOURCE_FILES})

find_package (Threads)
target_link_libraries (SMFLtest1 ${CMAKE_THREAD_LIBS_INIT})

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    #target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
    target_link_libraries(SMFLtest1 ${SFML_LIBRARIES})
endif()