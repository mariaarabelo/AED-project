cmake_minimum_required(VERSION 3.26)
project(AED_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(AED_project
        src/main.cpp
        src/File_Reader.cpp
        src/Lecture.cpp
        src/Class.cpp
        src/Student.h
        src/Student.cpp
        src/UC.cpp
        src/Schedule.h
        src/Schedule.cpp
        src/Application.h
        src/Application.cpp
        src/Interface.h
        src/Interface.cpp)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
endif()
