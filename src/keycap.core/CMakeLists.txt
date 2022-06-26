
add_library(keycap_core
	"algorithm.ixx"
	"concepts.ixx"
	"keycap.core.ixx"
	"math.ixx"
	"scopeguard.ixx"
	"string.ixx"
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
)