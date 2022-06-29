
# ---- Dependencies ----

#include(../../cmake/FindBotan.cmake)
#find_library(BOTAN2 botan2 PATHS BOTAN_INSTALL_PATH)


 find_package(Botan3)
# ---- The library ----

add_library(keycap_crypto
	"keycap.crypto.ixx"
	"OTP.ixx"
)
add_library(keycap::crypto ALIAS keycap_crypto)

set_property(TARGET keycap_crypto PROPERTY CMAKE_GENERATOR "msbuild")

target_include_directories(keycap_crypto
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(keycap_crypto
	PRIVATE
		keycap::project_options
        keycap::project_warnings
		keycap::core
		fmt::fmt
		Botan3::Botan3
)