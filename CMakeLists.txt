cmake_minimum_required(VERSION 3.29)

project(fix-entry-id VERSION 1.0.0 LANGUAGES CXX)

find_package(cifpp 7.0.9 REQUIRED)
find_package(gxrio REQUIRED)
find_package(Mrc REQUIRED)

add_executable(fix-entry-id fix-entry-id.cpp)

target_link_libraries(fix-entry-id ${ZLIB_LIBRARIES} cifpp::cifpp gxrio::gxrio)

mrc_target_resources(fix-entry-id ${CMAKE_CURRENT_SOURCE_DIR}/dssp-extension.dic)

install(TARGETS fix-entry-id DESTINATION ${CMAKE_INSTALL_BIN_DIR})
