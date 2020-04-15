cmake_minimum_required(VERSION 3.8)
project(maze)
set(PROJECT_VERSION 2.0)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../bin)

aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRC)


include_directories(${PROJECT_SOURCE_DIR}/src)

include_directories(${PROJECT_SOURCE_DIR}/include)


link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(main ${DIR_SRC})
