# get kernel sources
file(GLOB_RECURSE KERNEL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR} *.c *.cpp *.cxx)

# make a variable to point to kernel headers
set(KERNEL_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/headers)
set(KERNEL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/sources)
set(KERNEL_ROOT_DIR ${PROJECT_SOURCE_DIR}/kernel)

# make kernel as library
add_executable(daivik ${KERNEL_SOURCES})
# set include directories for kernel
target_include_directories(daivik PRIVATE ${KERNEL_HEADERS_DIR})
# set compile options
target_compile_options(daivik PRIVATE   -Wall -Wextra -O2 
                                        -ffreestanding       
                                        -fno-stack-protector 
                                        -fno-pic -fpie       
                                        -mgeneral-regs-only
                                        -fno-exceptions -fno-rtti
                                        -mno-red-zone)
# set linker options
target_link_options(daivik PRIVATE  -fno-pic -fpie 
                                    # this must be a comma separated list
                                    -Wl,-static,-pie,-ztext--no-dynamic-linker
                                    -static-pie 
                                    -nostdlib   
                                    -T${CMAKE_CURRENT_SOURCE_DIR}/linker.ld 
                                    -z max-page-size=0x1000)

# add install rules for this include dir
install(DIRECTORY ${KERNEL_HEADERS_DIR} DESTINATION ${CMAKE_INSTALL_PREFIX})
