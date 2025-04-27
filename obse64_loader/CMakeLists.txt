cmake_minimum_required(VERSION 3.18)

# ---- Project ----

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/versioning.cmake)

project(
	obse64_loader
	VERSION 1.0.0
	LANGUAGES CXX
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
	message(
		FATAL_ERROR
			"In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
)
endif()

# ---- Build options ----

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_DEBUG OFF)

# ---- Dependencies ----

if (NOT TARGET obse64_common)
	add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../obse64_common obse64_common)	# bundled
endif()

# ---- Add source files ----

file(GLOB headers CONFIGURE_DEPENDS *.h)
file(GLOB sources CONFIGURE_DEPENDS *.cpp)

source_group(
	${PROJECT_NAME}
	FILES
		${headers}
		${sources}
		obse64_loader_version.rc
		obse64_loader.manifest
)

# ---- Create library ----

add_executable(
	${PROJECT_NAME}
	${headers}
	${sources}
	obse64_loader_version.rc
	obse64_loader.manifest
)

add_executable(obse64::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/configuration.cmake)

target_compile_features(
	${PROJECT_NAME}
	PUBLIC
		cxx_std_17
)

target_compile_options(
	${PROJECT_NAME}
	PUBLIC
		$<$<CXX_COMPILER_ID:MSVC>:/wd4200>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wno-unused-parameter>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wno-unused-variable>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-fpermissive>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-fno-strict-aliasing>
)

target_include_directories(
	${PROJECT_NAME}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
		$<INSTALL_INTERFACE:include>
)

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
		obse64::obse64_common
		$<$<CXX_COMPILER_ID:MSVC>:Shlwapi.lib>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:shlwapi>
		$<$<CXX_COMPILER_ID:MSVC>:Version.lib>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:version>
		$<$<CXX_COMPILER_ID:MSVC>:Wintrust.lib>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:wintrust>
		$<$<CXX_COMPILER_ID:MSVC>:Crypt32.lib>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:crypt32>
)

# ---- Configure all targets ----

set_target_properties(
	${PROJECT_NAME}
	obse64_common
	PROPERTIES
		MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
)

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/installation.cmake)
