if(PROJECT_IS_TOP_LEVEL)
  set(CMAKE_INSTALL_INCLUDEDIR include/RPG CACHE PATH "")
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package RPG)

install(
    TARGETS RPG_exe
    EXPORT RPGTargets
    RUNTIME COMPONENT RPG_Runtime
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    RPG_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(RPG_INSTALL_CMAKEDIR)

install(
    FILES cmake/install-config.cmake
    DESTINATION "${RPG_INSTALL_CMAKEDIR}"
    RENAME "${package}Config.cmake"
    COMPONENT RPG_Development
)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${RPG_INSTALL_CMAKEDIR}"
    COMPONENT RPG_Development
)

install(
    EXPORT RPGTargets
    NAMESPACE RPG::
    DESTINATION "${RPG_INSTALL_CMAKEDIR}"
    COMPONENT RPG_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
