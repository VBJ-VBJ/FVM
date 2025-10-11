cmake_minimum_required(VERSION 3.10)
project(FVMProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add library and examples
add_subdirectory(src/FVM)
add_subdirectory(exemples/diffusion_stationnaire)
