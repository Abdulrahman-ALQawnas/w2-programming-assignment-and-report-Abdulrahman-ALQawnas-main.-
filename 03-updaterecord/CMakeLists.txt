cmake_minimum_required(VERSION 3.5)

project(updaterecord LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(updaterecord main.cpp
    studentrecord.cpp studentrecord.h testdb.cpp testdb.h)

include(GNUInstallDirs)
install(TARGETS updaterecord
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
