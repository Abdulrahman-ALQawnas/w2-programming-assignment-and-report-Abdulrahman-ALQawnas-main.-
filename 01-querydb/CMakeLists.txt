cmake_minimum_required(VERSION 3.5)

project(querydb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(querydb main.cpp
    testdb.cpp testdb.h
    studentrecord.h studentrecord.cpp)

include(GNUInstallDirs)
install(TARGETS querydb
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
