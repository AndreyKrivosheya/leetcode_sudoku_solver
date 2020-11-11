cmake_minimum_required(VERSION 3.18)

project(leetcode.sudoku_solver C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

####################################################################################################
# prepare googletest out of github repo
####################################################################################################
# Download and unpack googletest at configure time
configure_file(CMakeLists.gtest-download.txt googletest/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest"
)
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest"
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest/src" "${CMAKE_BINARY_DIR}/googletest/build")

####################################################################################################
# project targets
####################################################################################################
enable_testing()

# shared libraries
# per test projects
add_subdirectory(sudoku_solver)
