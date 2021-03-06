cmake_minimum_required(VERSION 3.5)

# set the project name
project(BooleanNetworkWebApp)

#set CMake Cpp standard
set(CMAKE_CXX_STANDARD 14)

#-----------------------------------------------------------------------------------------

find_package(Threads)
find_package(ZLIB)
find_package(OpenSSL)

if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "No build type selected, default to Release")
    set(CMAKE_BUILD_TYPE "Release")
endif()

add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)

if (MSVC)
    set(Boost_USE_STATIC_LIBS "On")
    find_package( Boost COMPONENTS system thread regex REQUIRED )
else()
    find_package( Boost COMPONENTS system thread REQUIRED )
endif()

include_directories(${Boost_INCLUDE_DIR})

include_directories(libs)

#-----------------------------------------------------------------------------------------

# add the executable
add_executable(sudoku src/main.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
target_link_libraries(sudoku PRIVATE Threads::Threads)

#-----------------------------------------------------------------------------------------

file(COPY src/index.html DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY src/shellScripts/deploy.sh DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY src/shellScripts/kill.sh DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY src/shellScripts/restart.sh DESTINATION ${CMAKE_CURRENT_BINARY_DIR})