cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    RPG
    VERSION 0.0.1
    DESCRIPTION "RPG Game"
    HOMEPAGE_URL "https://github.com/bensuperpc/RPG_project"
    LANGUAGES CXX
)

docs_early_return()

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    RPG_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    RPG_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(RPG_lib PUBLIC cxx_std_17)

# ---- Declare executable ----

add_executable(RPG_exe source/main.cpp)
add_executable(RPG::exe ALIAS RPG_exe)

set_target_properties(
    RPG_exe PROPERTIES
    OUTPUT_NAME RPG
    EXPORT_NAME exe
)

target_compile_features(RPG_exe PRIVATE cxx_std_17)

target_link_libraries(RPG_exe PRIVATE RPG_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT RPG_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of RPG"
  )
endif()

include(cmake/dev-mode.cmake)
