cmake_minimum_required(VERSION 3.23)

# Set the project name to your project name, my project isn't very descriptive
project(keycap VERSION 0.0.1 LANGUAGES CXX)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)
 
 set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

 set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "3c375311-a3c9-4396-a187-3227ef642046")
if(WIN32)
  include(cmake/msvc_modules.cmake)
else()
  include(cmake/gcc_modules.cmake)
endif()

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(keycap_project_options INTERFACE)
add_library(keycap::project_options ALIAS keycap_project_options)

set_target_properties(keycap_project_options PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(keycap_project_options INTERFACE cxx_std_23)

if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  option(ENABLE_BUILD_WITH_TIME_TRACE "Enable -ftime-trace to generate time tracing .json files on clang" OFF)
  if(ENABLE_BUILD_WITH_TIME_TRACE)
    target_compile_options(keycap_project_options INTERFACE -ftime-trace)
  endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
endif()

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(keycap_project_warnings INTERFACE)
add_library(keycap::project_warnings ALIAS keycap_project_warnings)

# Add linker configuration
include(cmake/Linker.cmake)
configure_linker(keycap_project_options)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(keycap_project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(keycap_project_options)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)
option(ENABLE_TESTING "Enable Test Builds" OFF)
option(ENABLE_FUZZING "Enable Fuzzing Builds" OFF)

if(ENABLE_TESTING)
  enable_testing()
  message("Building Tests.")
  add_subdirectory(test)
endif()

if(ENABLE_FUZZING)
  message("Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html")
  add_subdirectory(fuzz_test)
endif()

add_subdirectory(src)

option(ENABLE_UNITY "Enable Unity builds of projects" OFF)
if(ENABLE_UNITY)
  # Add for any project you want to apply unity builds for
  set_target_properties(intro PROPERTIES UNITY_BUILD ON)
endif()
