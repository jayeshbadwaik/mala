# We use GNU Install Paths
include(GNUInstallDirs)

# Install Target
install(
  TARGETS ${LIBNAME}
  EXPORT ${PROJECT_NAME}Target
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

install(
  EXPORT ${PROJECT_NAME}Target
  FILE  ${PROJECT_NAME}Target.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
  )

# Install Primary Headers
install(
  DIRECTORY ${PROJECT_SOURCE_DIR}/src/include
  DESTINATION  ${CMAKE_INSTALL_PREFIX}
  )

# Install Library
add_library(${PROJECT_NAME}::${LIBNAME} ALIAS ${LIBNAME})

# Install Configuration Files
install(
  FILES
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  ${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/apache.license
  ${PROJECT_SOURCE_DIR}/mit.license
  ${PROJECT_SOURCE_DIR}/copyright.md
  DESTINATION  ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/
  )

install(
  FILES ${PROJECT_SOURCE_DIR}/copyright.md
  DESTINATION  ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}/copyright
  )


if(BUILD_DOC)
  if (DOXYGEN_FOUND)
    install(
      DIRECTORY ${PROJECT_BINARY_DIR}/doc/
      DESTINATION ${CMAKE_INSTALL_DOCDIR}/
      )
  endif ()
endif ()


