cmake_minimum_required(VERSION 3.0)
project(CrfsuiteHeaders)

# Define header files
set(CRFSUITE_HEADERS
        crfsuite.h
        crfsuite_api.hpp
        crfsuite.hpp
        )

# Specify the include directory
include_directories(${CMAKE_SOURCE_DIR})

# Install the header files
install(FILES ${CRFSUITE_HEADERS} DESTINATION include/crfsuite)