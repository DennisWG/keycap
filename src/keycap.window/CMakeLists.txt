
# ---- Dependencies ----

include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY "https://github.com/glfw/glfw"
        GIT_TAG "45ce5ddd197d5c58f50fdd3296a5131c894e5527" # 3.3.7
)

FetchContent_MakeAvailable(glfw)

# ---- The library ----

add_library(keycap_window
	"keycap.window.ixx"
 "window.ixx" "input_mappings.ixx" "input_events.ixx" "fragments.ixx")
add_library(keycap::window ALIAS keycap_window)

set_property(TARGET keycap_window PROPERTY CMAKE_GENERATOR "msbuild")

target_include_directories(keycap_window
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(keycap_window
	PRIVATE
		keycap::project_options
        keycap::project_warnings
		keycap::core
		fmt::fmt
		glfw
)