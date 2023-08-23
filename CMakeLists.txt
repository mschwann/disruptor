# Works with 3.14 and tested through 3.27
cmake_minimum_required(VERSION 3.14...3.27)

# Project name and a few useful settings. Other commands can pick up the results
project(
  Disruptor
  VERSION 0.0.0
  DESCRIPTION "Experiments with disruptor"
  LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "-O3")

include(FetchContent)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here

  # Let's ensure -std=c++xx instead of -std=g++xx
  set(CMAKE_CXX_EXTENSIONS OFF)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        release-1.12.1
  )
  FetchContent_MakeAvailable(googletest)

  FetchContent_Declare(
    benchmark
    GIT_REPOSITORY  https://github.com/google/benchmark.git
    GIT_TAG         v1.8.2
  )
  FetchContent_MakeAvailable(benchmark)
endif()

# Formatting library
#FetchContent_Declare(
#  fmtlib
#  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#  GIT_TAG 5.3.0)
#FetchContent_MakeAvailable(fmtlib)
# Adds fmt::fmt

include(cmake/setup.cmake)
add_subdirectory(src)
