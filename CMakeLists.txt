cmake_minimum_required(VERSION 3.10)
project(FVMProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add library and examples
add_subdirectory(src/FVM)
add_subdirectory(exemples/diffusion_stationnaire_1D)
add_subdirectory(exemples/diffusion_stationnaire_2D)

# Documentation (Doxygen)
find_package(Doxygen QUIET)

if (DOXYGEN_FOUND)
    message(STATUS "Doxygen found, creating 'doc' target")

    # Check for dot (graphviz) for nicer graphs in the output
    find_program(DOT_EXECUTABLE dot)
    if(NOT DOT_EXECUTABLE)
        message(WARNING "Graphviz 'dot' not found. Graphs will not be generated. Install graphviz to enable graphs.")
    endif()

    set(DOXYFILE_IN ${CMAKE_SOURCE_DIR}/Doxyfile)
    set(DOXY_OUT_DIR ${CMAKE_SOURCE_DIR}/doc)

    # Custom target that regenerates documentation
    add_custom_target(doc
        COMMAND ${CMAKE_COMMAND} -E remove_directory ${DOXY_OUT_DIR}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${DOXY_OUT_DIR}
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_IN}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )

    add_custom_command(TARGET doc POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Doxygen HTML output available at: ${DOXY_OUT_DIR}/html/index.html"
    )

else()
    message(WARNING "Doxygen not found. Run 'sudo apt install doxygen' (or your distro equivalent) to enable documentation generation.")
endif()