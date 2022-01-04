cmake_minimum_required(VERSION 3.10)

# set the project name
project(bloom)
project(bloom VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# set(CMAKE_BUILD_TYPE Debug)

include_directories(${CMAKE_BINARY_DIR})

set(CMAKE_CXX_FLAGS "-Wall -Ofast -g")

set(SRCS
  main.cpp
  seq_reader.cpp
  kmer.cpp
  bloom.cpp
  hash.cpp
  )

set(HEADERS
  seq_reader.hpp
  kmer.hpp
  bloom.hpp
  hash.hpp
  )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

# add the executable
add_executable(bloom_test main.cpp ${SRCS})

# add_library(kff ${SRCS})
# target_include_directories(kff PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
