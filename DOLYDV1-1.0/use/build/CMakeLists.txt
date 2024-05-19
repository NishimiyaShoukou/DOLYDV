# Set the minimum required CMake version
cmake_minimum_required (VERSION 2.8)
# set the project name
project (doly_cmake)

# Locate main source files
aux_source_directory(${PROJECT_BINARY_DIR}/../ SRC_MAIN) 
aux_source_directory(${PROJECT_BINARY_DIR}/../init SRC_INIT) 
# Include directories for public headers and application headers
include_directories (${PROJECT_BINARY_DIR}/../../include/pub)
include_directories (${PROJECT_BINARY_DIR}/../../app/AppDoly)
include_directories (${PROJECT_BINARY_DIR}/../init)
# find_library(FUNC_LIB ${PROJECT_BINARY_DIR}/../lib)
file(GLOB FUNC_LIB ${PROJECT_BINARY_DIR}/../lib/*.a ${PROJECT_BINARY_DIR}/../lib/*.so)


# Set the output path for executables
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)



# Add compiler options
add_compile_options(-Wall)
# add the executable
add_executable(doly_core ${SRC_MAIN})

message("FUNC_LIB = ${FUNC_LIB}")
message("SRC_INIT = ${SRC_INIT}")
message("SRC_MAIN = ${SRC_MAIN}")
# Link the executable with the found libraries
target_link_libraries(doly_core PUBLIC 
                        -Wl,--start-group
                        ${FUNC_LIB}
                        -lpthread
                        -Wl,--end-group
                      )

