cmake_minimum_required(VERSION 3.9)

project(modules CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(Boost COMPONENTS python3 REQUIRED)
find_package(PythonLibs REQUIRED)

python_add_module(internals src/internals.cpp)
target_link_libraries(internals ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
target_include_directories(internals PRIVATE include/ ${Boost_INCLUDE_DIR} ${PYTHON_INCLUDE_DIRS})

install(TARGETS internals DESTINATION modules)
install(FILES modules/arithmetic.py modules/colors.py modules/string.py DESTINATION modules)

add_library(modules INTERFACE)
include(GNUInstallDirs)

target_include_directories(
        modules INTERFACE
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(
        TARGETS modules
        EXPORT modules-config)

install(
        EXPORT modules-config
        NAMESPACE modules::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/modules)

install(
        DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/modules)