cmake_minimum_required(VERSION 3.1...3.14)

# Define header files
set(CRFSUITE_HEADERS
        crfsuite.h
        crfsuite_api.hpp
        crfsuite.hpp
        os.h
        )

# Specify the include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Install the header files
install(FILES ${CRFSUITE_HEADERS} DESTINATION include/crfsuite)