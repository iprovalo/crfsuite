cmake_minimum_required(VERSION 3.1...3.14)

# Include directories
include_directories(include)

# Source files
set(SOURCES
        src/lookup3.c
        src/cqdb.c
        )

# Add library target
add_library(cqdb STATIC ${SOURCES})

# Set properties and compile options
set_target_properties(cqdb PROPERTIES
        VERSION ${VERSION}
        SOVERSION ${VERSION}
        )

# Adding compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I./include")

# Specify install rules (optional)
install(TARGETS cqdb DESTINATION lib)
install(FILES include/cqdb.h DESTINATION include)

