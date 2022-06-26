cmake_minimum_required(VERSION 3.15...3.23)

project(CmakeConfigPackageTests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()

  find_package(keycap CONFIG REQUIRED) # for intro, project_options, ...

  if(NOT TARGET keycap_project_options)
    message(FATAL_ERROR "Requiered config package not found!")
    return() # be strictly paranoid for Template Janitor github action! CK
  endif()
endif()

# ---- Dependencies ----

include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY "https://github.com/catchorg/Catch2"
        GIT_TAG "605a34765aa5d5ecbf476b4598a862ada971b0cc" # v3.0.1
)

FetchContent_MakeAvailable(Catch2)

include(Catch)

add_executable(tests
    "tests.keycap.core.cpp"
    "tests.keycap.window.cpp"
)
target_link_libraries(tests PRIVATE keycap::core keycap::window keycap::project_warnings keycap::project_options Catch2WithMain fmt::fmt)
set_target_properties(tests PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(tests PUBLIC cxx_std_23)

# automatically discover tests that are defined in catch based test files you can modify the unittests. Set TEST_PREFIX
# to whatever you want, or use different for different binaries
catch_discover_tests(
  tests
  TEST_PREFIX
  "unittests."
  REPORTER
  console
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "unittests."
  OUTPUT_SUFFIX
  .xml)

# Add a file containing a set of constexpr tests
add_executable(constexpr_tests constexpr_tests.cpp)
target_link_libraries(constexpr_tests PRIVATE keycap::core keycap::project_warnings keycap::project_options Catch2WithMain )
set_target_properties(constexpr_tests PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(constexpr_tests PUBLIC cxx_std_23)

catch_discover_tests(
  constexpr_tests
  TEST_PREFIX
  "constexpr."
  REPORTER
  console
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "constexpr."
  OUTPUT_SUFFIX
  .xml)

# Disable the constexpr portion of the test, and build again this allows us to have an executable that we can debug when
# things go wrong with the constexpr testing
add_executable(relaxed_constexpr_tests constexpr_tests.cpp)
target_link_libraries(relaxed_constexpr_tests PRIVATE keycap::core keycap::project_warnings keycap::project_options Catch2WithMain )
target_compile_definitions(relaxed_constexpr_tests PRIVATE -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)
set_target_properties(relaxed_constexpr_tests PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(relaxed_constexpr_tests PUBLIC cxx_std_23)

catch_discover_tests(
  relaxed_constexpr_tests
  TEST_PREFIX
  "relaxed_constexpr."
  REPORTER
  console
  OUTPUT_DIR
  .
  OUTPUT_PREFIX
  "relaxed_constexpr."
  OUTPUT_SUFFIX
  .xml)
