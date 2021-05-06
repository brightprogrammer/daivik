# get kernel sources
file(GLOB_RECURSE KERNEL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR} *.c *.cpp *.cxx)

# make kernel as library
add_library(daivik_kernel STATIC ${KERNEL_SOURCES})
target_include_directories(daivik_kernel PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(daivik_kernel PRIVATE -Wall -Wextra -O2 -Tlinker.ld)

execute_process(COMMAND cp ${PROJECT_BINARY_DIR}/kernel/libdaivik_kernel.a ${PROJECT_BINARY_DIR}/daivik.elf)