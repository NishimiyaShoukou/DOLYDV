# request version
cmake_minimum_required (VERSION 2.8)

project (doly_cmake)

aux_source_directory(${PROJECT_BINARY_DIR}/../init SRC_MAIN) 

include_directories (${PROJECT_BINARY_DIR}/../../include/pub)
include_directories (${PROJECT_BINARY_DIR}/../../app/AppDoly)
# find_library(FUNC_LIB ${PROJECT_BINARY_DIR}/../lib)
file(GLOB FUNC_LIB ${PROJECT_BINARY_DIR}/../lib/*.a ${PROJECT_BINARY_DIR}/../lib/*.so)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

LINK_LIBRARIES(-lpthread)

add_compile_options(-Wall)

add_executable(doly_core ${SRC_MAIN})


target_link_libraries(doly_core ${FUNC_LIB})
