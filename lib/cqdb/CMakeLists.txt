cmake_minimum_required(VERSION 3.0)
project(LibCqdb)

# Set the version (replace '1.0.0' with your actual version)
set(VERSION 1.0.0)

# Include directories
include_directories(include)

# Source files
set(SOURCES
        src/lookup3.c
        src/cqdb.c
        )

# Add library target
add_library(cqdb ${SOURCES})

# Set properties and compile options
set_target_properties(cqdb PROPERTIES
        VERSION ${VERSION}
        SOVERSION ${VERSION}
        )

# Adding compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I./include")

# Assuming this is a shared library and ensuring undefined symbols are not allowed
set_target_properties(cqdb PROPERTIES
        LINK_FLAGS "-no-undefined"
        )

# Specify install rules (optional)
install(TARGETS cqdb DESTINATION lib)
install(FILES include/cqdb.h DESTINATION include)
