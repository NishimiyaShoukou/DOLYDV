# Set the minimum required CMake version
cmake_minimum_required (VERSION 2.8)

# Set the project name
project (doly_cmake)

# Locate source files within the AppDoly directory
aux_source_directory(${PROJECT_BINARY_DIR}/../src SRC_MOV) 

# Include directories for public headers
include_directories (${PROJECT_BINARY_DIR}/../../include/pub)
include_directories (${PROJECT_BINARY_DIR}/../inc)
# Add compiler options to enable Wall warnings
add_compile_options(-Wall)

# Create a static library from the source files
add_library(movebase_static STATIC ${SRC_MOV})

# Set the output name of the static library to "gui"
set_target_properties(movebase_static PROPERTIES OUTPUT_NAME "movebase")

# Set the output path for the library
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../use/lib)
