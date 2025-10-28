cmake_minimum_required(VERSION 3.10)
project(diffusion_stationnaire LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Example executable (the FVM library is expected to be provided by the top-level project)
add_executable(diffusion_stationnaire_2D main.cpp)

target_link_libraries(diffusion_stationnaire_2D PRIVATE FVM)

target_include_directories(diffusion_stationnaire_2D PRIVATE ${CMAKE_SOURCE_DIR}/include)
