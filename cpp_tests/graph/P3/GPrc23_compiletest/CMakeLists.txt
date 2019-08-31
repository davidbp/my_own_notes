cmake_minimum_required (VERSION 3.0.1)
project (Graphs_P3)



 


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "AppleClang")
   # TODO

elseif (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU"))
   # using Clang or GCC

   # all warnings are considered errors
   #set(COMMON_CXX_FLAGS "-Wall -Werror -Wtype-limits -Wshadow -Wcast-align -Wempty-body -Wpointer-arith -Wendif-labels -Wundef -Wredundant-decls")

   # some basic performance flags
   set(COMMON_CXX_FLAGS "${COMMON_CXX_FLAGS} -O3 -mtune=native -march=native")

   # C++ standard
   set(COMMON_CXX_FLAGS "${COMMON_CXX_FLAGS} -std=c++14")

   # some debug flags
   set(COMMON_CXX_FLAGS "${COMMON_CXX_FLAGS} -g")


elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
   # using Visual Studio C++

endif()




# Set CPPFLAGS
set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${COMMON_CXX_FLAGS}")


# Get automatically all source files from src directory
file(GLOB SOURCE_FILES_CPP "${CMAKE_SOURCE_DIR}/src/*.cpp")


# Copy input files to build location
file(GLOB TEST_DATASETS "${CMAKE_SOURCE_DIR}/input/*.in")
file(COPY ${TEST_DATASETS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)



# Create target exec
add_executable(p3 ${SOURCE_FILES_CPP})

