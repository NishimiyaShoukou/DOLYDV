
# Set the minimum required CMake version
cmake_minimum_required (VERSION 2.8)

# Set the project name
project (doly_cmake)

# Locate source files within the AppDoly directory
aux_source_directory(${PROJECT_BINARY_DIR}/../tcp SRC_COMMU) 

# Include directories for public headers
include_directories (${PROJECT_BINARY_DIR}/../../include/pub)
include_directories (${PROJECT_BINARY_DIR}/../tcp)
# Add compiler options to enable Wall warnings
add_compile_options(-Wall)

# Create a static library from the source files
add_library(commu_static STATIC ${SRC_COMMU})

# Set the output name of the static library to "gui"
set_target_properties(commu_static PROPERTIES OUTPUT_NAME "commu")

# Set the output path for the library
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../use/lib)

