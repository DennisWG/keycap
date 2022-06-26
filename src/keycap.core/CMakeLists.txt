
# ---- Dependencies ----

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY "https://github.com/fmtlib/fmt"
        GIT_TAG "b6f4ceaed0a0a24ccf575fab6c56dd50ccf6f1a9" # 8.1.1
)

FetchContent_Declare(
        backward
        GIT_REPOSITORY "https://github.com/bombela/backward-cpp"
        GIT_TAG "74184aad55777f0c04227edd56c3dea84b6a272f" # 08. June 2022
)

FetchContent_MakeAvailable(fmt backward)

# ---- The library ----

add_library(keycap_core
	"algorithm.ixx"
	"concepts.ixx"
	"error.ixx"
	"fragments.ixx"
	"keycap.core.ixx"
	"math.ixx"
	"scopeguard.ixx"
	"string.ixx"
	"types.ixx"
)
add_library(keycap::core ALIAS keycap_core)

set_property(TARGET keycap_core PROPERTY CMAKE_GENERATOR "msbuild")

target_include_directories(keycap_core
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(keycap_core
	PRIVATE
		keycap::project_options
        keycap::project_warnings
		fmt::fmt
		backward
)