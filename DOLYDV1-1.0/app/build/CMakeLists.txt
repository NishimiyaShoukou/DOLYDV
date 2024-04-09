# request version
cmake_minimum_required (VERSION 2.8)

project (doly_cmake)

aux_source_directory(${PROJECT_BINARY_DIR}/../AppDoly SRC_APP) 

include_directories (${PROJECT_BINARY_DIR}/../../include/pub)

add_compile_options(-Wall)

#add_library(app_shared SHARED ${SRC_APP})
add_library(app_static STATIC ${SRC_APP})

set_target_properties(app_static PROPERTIES OUTPUT_NAME "app")

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../use/lib)

