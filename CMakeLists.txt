cmake_minimum_required(VERSION 3.5)

# project settings
project(daivik VERSION "${PROJECT_VERSION}" LANGUAGES C CXX)

# set install dir to sysroot/usr - our new operating system
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/sysroot/usr)

add_subdirectory(kernel)