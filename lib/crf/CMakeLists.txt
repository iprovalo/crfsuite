cmake_minimum_required(VERSION 3.1...3.14)

# Define the version number (update this as needed)
set(VERSION 1.0.0)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/lib/cqdb/include)

# Source files
set(SOURCES
        src/dictionary.c
        src/logging.c
        src/logging.h
        src/params.c
        src/params.h
        src/quark.c
        src/quark.h
        src/rumavl.c
        src/rumavl.h
        src/vecmath.h
        src/crfsuite_internal.h
        src/dataset.c
        src/holdout.c
        src/train_arow.c
        src/train_averaged_perceptron.c
        src/train_l2sgd.c
        src/train_lbfgs.c
        src/train_passive_aggressive.c
        src/crf1d.h
        src/crf1d_context.c
        src/crf1d_model.c
        src/crf1d_feature.c
        src/crf1d_encode.c
        src/crf1d_tag.c
        src/crfsuite_train.c
        src/crfsuite.c
        )

# Create a shared library
add_library(crfsuite SHARED ${SOURCES})

# Set library version
set_target_properties(crfsuite PROPERTIES VERSION ${VERSION})

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -I${CMAKE_SOURCE_DIR}/lib/cqdb/include")

# Linker flags
set_target_properties(crfsuite PROPERTIES
        LINK_FLAGS "-no-undefined"
        )

# Link against libcqdb (update this path as needed)
# Assuming libcqdb is built and findable by CMake
find_library(CQDB_LIBRARY NAMES cqdb PATHS "${CMAKE_SOURCE_DIR}/lib/cqdb")
target_link_libraries(crfsuite PRIVATE cqdb)

# Installation rules
install(TARGETS crfsuite DESTINATION lib)
