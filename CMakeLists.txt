cmake_minimum_required(VERSION 3.5)

# project settings
project(daivik VERSION "${PROJECT_VERSION}" LANGUAGES C CXX)

# set install dir to sysroot/program - our new operating system
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/sysroot/program)

# kernel directory
add_subdirectory(kernel)