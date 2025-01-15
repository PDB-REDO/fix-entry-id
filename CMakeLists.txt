cmake_minimum_required(VERSION 3.29)

project(fix-id VERSION 1.0.0 LANGUAGES CXX)

find_package(cifpp 7.0.9 REQUIRED)
find_package(gxrio REQUIRED)
find_package(Mrc REQUIRED)

add_executable(fix-id fix-id.cpp)

target_link_libraries(fix-id ${ZLIB_LIBRARIES} cifpp::cifpp gxrio::gxrio)

mrc_target_resources(fix-id ${CMAKE_CURRENT_SOURCE_DIR}/dssp-extension.dic)