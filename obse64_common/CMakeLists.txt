cmake_minimum_required(VERSION 3.18)

# ---- Project ----

include(${CMAKE_CURRENT_SOURCE_DIR}/../cmake/versioning.cmake)

project(
	obse64_common
	VERSION ${OBSE_VERSION_MAJOR}.${OBSE_VERSION_MINOR}.${OBSE_VERSION_PATCH}
	LANGUAGES CXX
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
	message(
		FATAL_ERROR
			"In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
)
endif()

# ---- Add source files ----

set(headers
	BranchTrampoline.h
	BufferStream.h
	CoreInfo.h
	DataStream.h
	DirectoryIterator.h
	Errors.h
	FileStream.h
	Log.h
	obse64_version.h
	Relocation.h
	SafeWrite.h
	Types.h
	Utilities.h
	MinGWDebug.h
)

set(sources
	BranchTrampoline.cpp
	BufferStream.cpp
	DataStream.cpp
	DirectoryIterator.cpp
	Errors.cpp
	FileStream.cpp
	Log.cpp
	Relocation.cpp
	SafeWrite.cpp
	Utilities.cpp
	MinGWDebug.cpp
)

source_group(
	${PROJECT_NAME}
	FILES
		${headers}
		${sources}
)

# ---- Create library ----

add_library(
	${PROJECT_NAME}
	STATIC
	${headers}
	${sources}
)

add_library(obse64::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_compile_features(
	${PROJECT_NAME}
	PUBLIC
		cxx_std_11
)

target_include_directories(
	${PROJECT_NAME}
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
		$<INSTALL_INTERFACE:include>
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

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
)

# ---- Create an installable target ----

include(GNUInstallDirs)

install(
	TARGETS
		${PROJECT_NAME}
	EXPORT
		${PROJECT_NAME}-targets
)

install(
	FILES
		${headers}
	DESTINATION
		${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
)

configure_file(
	cmake/config.cmake.in
	${PROJECT_NAME}-config.cmake
	@ONLY
)

install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
	DESTINATION
		${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

install(
	EXPORT
		${PROJECT_NAME}-targets
	NAMESPACE
		obse64::
	DESTINATION
		${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
