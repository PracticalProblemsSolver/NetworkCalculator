include(FetchContent)

cmake_minimum_required(VERSION 3.23)
project(CSCalculator)

set(CMAKE_CXX_STANDARD 14)

set(SERVER_SOURCES server.cpp
        functions/interactions.cpp
        functions/interactions.hpp
        functions/handling.cpp
        functions/handling.hpp
        functions/calc.cpp
        functions/calc.hpp)

set(CLIENT_SOURCES client.cpp
        functions/interactions.cpp
        functions/interactions.hpp)

FetchContent_Declare(
        libpqxx
        GIT_REPOSITORY https://github.com/jtv/libpqxx.git
        GIT_TAG a6b1d60e74c1427c8ac2324b85cd4a0dc2068332
)
set(PQXX_LIBRARIES pqxx_static)
set(SKIP_BUILD_TEST ON)

FetchContent_MakeAvailable(libpqxx)

add_executable(server.o ${SERVER_SOURCES})
add_executable(client.o ${CLIENT_SOURCES})

TARGET_LINK_LIBRARIES(server.o  "${PQXX_LIBRARIES}")