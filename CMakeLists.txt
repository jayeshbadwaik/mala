cmake_minimum_required(VERSION 3.12)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/module")

project(
  mala
  VERSION 0.0.1
  DESCRIPTION "mala"
  LANGUAGES CXX
  HOMEPAGE_URL "https://github.com/jayeshbadwaik/mala"
  )

set(CMAKE_DEBUG_POSTFIX -debug)

set(LIBNAME "lib${PROJECT_NAME}")
add_library(${LIBNAME})
set_target_properties(${LIBNAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

include(cmake/include/option.cmake)
include(cmake/include/configure.cmake)
include(cmake/include/documentation.cmake)

add_subdirectory(src)

include(CTest)
if (BUILD_TESTING)
  add_subdirectory(test)
endif()

include(cmake/include/install.cmake)
