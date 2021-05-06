# get kernel sources
file(GLOB_RECURSE KERNEL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR} *.c *.cpp *.cxx)

# make kernel as library
add_executable(daivik ${CMAKE_CURRENT_SOURCE_DIR}/source/kernel.cxx)
target_include_directories(daivik PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# set compile options
target_compile_options(daivik PRIVATE   -Wall -Wextra -O2 
                                        -ffreestanding       
                                        -fno-stack-protector 
                                        -fno-pic -fpie       
                                        -mgeneral-regs-only
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
install(DIRECTORY ${PROJECT_SOURCE_DIR}/kernel/include DESTINATION ${CMAKE_INSTALL_PREFIX})
