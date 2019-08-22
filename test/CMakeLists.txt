set(TESTLIBNAME "libtest${PROJECT_NAME}")
add_library(${TESTLIBNAME})
set_target_properties(${TESTLIBNAME} PROPERTIES OUTPUT_NAME "test${PROJECT_NAME}")
target_link_libraries(${TESTLIBNAME} PUBLIC ${LIBNAME})

include(${PROJECT_SOURCE_DIR}/cmake/include/test-external.cmake)

# Add Include Directories for Testing
target_include_directories(
  ${TESTLIBNAME} PUBLIC
  ${PROJECT_SOURCE_DIR}/test/include
  )

add_subdirectory(bin)
add_subdirectory(lib)

include(${PROJECT_SOURCE_DIR}/cmake/include/test-dependency.cmake)
