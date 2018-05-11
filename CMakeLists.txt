
# This is an #inglued <> generated CMakeLists.txt (https://github.com/header-only/inglued)
# To modify it edit CMakeLists.txt.tpl ( i.e. Generate it with `inglued cmaketpl` )


# This is an #inglued <> template !
#
# The template is processed by http://mustache.github.io/, more info about
# syntax here : http://mustache.github.io/mustache.5.html 
#
# You can access the following variables : 
# * cpp-pre : github organization name
# * named_param : current project name
# * . : current project srcs folder.
#
# *   : all deps direct and transitive 
#   -  : The cmake package name from the cmake_package_map otherwise: cpp-pre
#   -  : The cmake target name from cmake_package_map otherwise: ::
#   - cpp-pre : the github organization name
#   -  : the dependency repository name
#   -  : tag or branch wished for the dep
#   -  : the path you specified in deps/inglued -I
#   -  : same as above but with a guaranteed end slash.
#

cmake_minimum_required(VERSION 3.7.2)

project(named_param VERSION "0.0.1")
enable_testing()

# Compile with shipped-with headers or without 
option(INGLUED "Enable use of #inglued shipped with dependencies." ON)

# Compile unit tests
option(UNIT_TESTS "Enable Unit Testing" OFF)


# Warning as errors to ensure named_param quality
string(TOUPPER "${CMAKE_CXX_COMPILER_ID}" COMPILER_IN_USE)
if ("${COMPILER_IN_USE}" STREQUAL "GNU" OR "${COMPILER_IN_USE}" MATCHES "CLANG")
	add_definitions(
    -Wall
		-Werror
		-Wno-unused-local-typedefs
		-Wno-unused-variable
  )
endif()



# preprocess
if (INGLUED)
  include_directories(AFTER deps/cpp-pre/preprocess/)
else ()
  find_package(cpp-pre REQUIRED)
endif()


# Define header only library
include_directories(BEFORE ${CMAKE_CURRENT_LIST_DIR})
add_library(named_param INTERFACE)
add_library(cpp-pre::named_param ALIAS named_param)

set(include_install_dir "include")

if (INGLUED)

  target_include_directories(named_param INTERFACE 
    # Transitive libraries location once installed
    $<INSTALL_INTERFACE:${include_install_dir}/./deps> 
  )


else()

  target_link_libraries(named_param INTERFACE 
      cpp-pre::preprocess
  )

endif()


if( UNIT_TESTS )
 add_subdirectory(examples)
endif()

# IDE Supports (XCode, VS, QtCreator they don't list headers)
file (GLOB_RECURSE HPP_FILES ./*.h*)
add_custom_target(sources SOURCES ${HPP_FILES})

# Installing

# Layout. This works for all platforms:
#   * <prefix>/lib/cmake/<PROJECT-NAME>
#   * <prefix>/lib/
#   * <prefix>/include/
set(config_install_dir "lib/cmake/${PROJECT_NAME}")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Note: PROJECT_VERSION is used as a VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * targets_export_name
#   * PROJECT_NAME
configure_package_config_file(
    "cmake/modules/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)


# Targets:
install(
    TARGETS named_param
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)

# Headers:
install(
    DIRECTORY .
    DESTINATION "${include_install_dir}"
    FILES_MATCHING PATTERN "*.[ih]*"
)

# Install the deps when run in INGLUED mode
if (INGLUED)


  install(
      DIRECTORY deps/cpp-pre/preprocess/
      DESTINATION ${include_install_dir}/./deps
      FILES_MATCHING PATTERN "*.[ih]*"
      PATTERN deps/cpp-pre/preprocess/deps EXCLUDE # Transitive deps are hikedup on `glue seal`.
      )


endif(INGLUED)

# Config
#   * <prefix>/lib/cmake/named_param/named_paramConfig.cmake
#   * <prefix>/lib/cmake/named_param/named_paramConfigVersion.cmake
#   * <prefix>/lib/cmake/named_param/named_paramTargets.cmake
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)
install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)

