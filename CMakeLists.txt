cmake_minimum_required(VERSION 3.8)
project(cpp_zia)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/main.cpp src/SocketServer.cpp include/SocketServer.h src/Socket.cpp include/Socket.h src/StyleParser.cpp include/StyleParser.h)
add_executable(cpp_zia ${SOURCE_FILES})