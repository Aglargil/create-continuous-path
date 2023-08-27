cmake_minimum_required(VERSION 3.0.0)
project(CreateContinuousPath VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# matplot
include(FetchContent)
FetchContent_Declare(matplotplusplus
  GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
  GIT_TAG origin/master) # or whatever tag you want
FetchContent_GetProperties(matplotplusplus)

if(NOT matplotplusplus_POPULATED)
  FetchContent_Populate(matplotplusplus)
  add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

add_executable(CreateContinuousPath main.cpp)
target_link_libraries(${PROJECT_NAME} matplot)
