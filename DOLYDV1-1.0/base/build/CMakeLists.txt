# Set the minimum required CMake version
cmake_minimum_required (VERSION 2.8)

# Set the project name
project (doly_cmake)

# Locate source files within the AppDoly directory
aux_source_directory(${PROJECT_BINARY_DIR}/../kernel_dir SRC_BASE) 

# Include directories for public headers
include_directories (${PROJECT_BINARY_DIR}/../../include/pub)
include_directories (${PROJECT_BINARY_DIR}/../kernel_dir)
# Add compiler options to enable Wall warnings
add_compile_options(-Wall)
# Link the system library
LINK_LIBRARIES(-lpthread)

file(GLOB FUNC_LIB ${PROJECT_BINARY_DIR}/../../use/lib/*.a ${PROJECT_BINARY_DIR}/../../use/lib/*.so)

# Create a static library from the source files
add_library(base_static STATIC ${SRC_BASE})
message("FUNC_LIB = ${FUNC_LIB}")
target_link_libraries(base_static  ${FUNC_LIB})
# Set the output name of the static library to "app"
set_target_properties(base_static PROPERTIES OUTPUT_NAME "base")

# Set the output path for the library
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../use/lib)
