# Set the minimum required CMake version
cmake_minimum_required (VERSION 2.8)

# Set the project name
project (doly_cmake)

# Locate source files within the AppDoly directory
aux_source_directory(${PROJECT_BINARY_DIR}/../AppDoly/src SRC_APP) 
aux_source_directory(${PROJECT_BINARY_DIR}/../movebase/src SRC_MOVEBASE) 
# Include directories for public headers
include_directories (${PROJECT_BINARY_DIR}/../../include/pub)
# Include directories for base headers
include_directories (${PROJECT_BINARY_DIR}/../AppDoly/inc)
include_directories (${PROJECT_BINARY_DIR}/../movebase/inc)
include_directories (${PROJECT_BINARY_DIR}/../../base/kernel_dir)
include_directories (${PROJECT_BINARY_DIR}/../../gui/eye)

# Add compiler options to enable Wall warnings
add_compile_options(-Wall)
# Link the system library
LINK_LIBRARIES(-lpthread)

file(GLOB FUNC_LIB ${PROJECT_BINARY_DIR}/../../use/lib/*.a ${PROJECT_BINARY_DIR}/../../use/lib/*.so)

# Create a static library from the source files

add_library(app_static STATIC ${SRC_APP} ${SRC_MOVEBASE})
message("FUNC_LIB = ${FUNC_LIB}")
# target_link_libraries(app_static  ${FUNC_LIB})
# Set the output name of the static library to "app"
set_target_properties(app_static PROPERTIES OUTPUT_NAME "app")

# Set the output path for the library
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../use/lib)
