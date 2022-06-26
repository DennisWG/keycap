
add_library(keycap_keycap
	"scopeguard.ixx"
	"concepts.ixx"
	"math.ixx"
	"string.ixx"
	"keycap.ixx"
)
add_library(keycap::keycap ALIAS keycap_keycap)

set_property(TARGET keycap_keycap PROPERTY CMAKE_GENERATOR "msbuild")

target_include_directories(keycap_keycap
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(keycap_keycap
	PRIVATE
		keycap::project_options
        keycap::project_warnings
)