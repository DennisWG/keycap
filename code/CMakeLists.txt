
add_library(keycap_keycap
	"keycap/scopeguard.ixx"
	"keycap/concepts.ixx"
	"keycap/math.ixx"
	"keycap/string.ixx"
	"keycap.ixx"
)

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
		keycap_project_options
        keycap_project_warnings
)