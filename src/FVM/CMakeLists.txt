cmake_minimum_required(VERSION 3.10)
project(FVMLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files for the FVM library
set(FVM_SRC
    # /Core
    ${CMAKE_CURRENT_LIST_DIR}/Core/Field.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/Mesh2D.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Core/Vertex2D.cpp
    # /I_O
    ${CMAKE_CURRENT_LIST_DIR}/I_O/MeshFactory.cpp
    # /LinearSolver  
	${CMAKE_CURRENT_LIST_DIR}/LinearSolver/SparseMatrixDIA.cpp
	${CMAKE_CURRENT_LIST_DIR}/LinearSolver/Vectorb.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LinearSolver/GaussSeidelSolver.cpp
)

add_library(FVM STATIC ${FVM_SRC})

# Public include directory (root project's include/ folder)
target_include_directories(FVM PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_compile_features(FVM PUBLIC cxx_std_17)
