cmake_minimum_required(VERSION 3.1...3.14)
#project(liblbfgs)

# Define the version number (replace with actual version)
set(VERSION 1.0.0)

# Specify the C++ standard, if necessary
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# List of source files
set(SOURCES
        lib/arithmetic_ansi.h
        lib/arithmetic_sse_double.h
        lib/arithmetic_sse_float.h
        lib/lbfgs.c
        )

# Create a library target
add_library(lbfgs ${SOURCES})

# Set library properties for version and soversion
set_target_properties(lbfgs PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION})

# Installation rules for the library and header files
install(TARGETS lbfgs DESTINATION lib)
install(FILES include/lbfgs.h DESTINATION include)
