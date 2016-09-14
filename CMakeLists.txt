# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 3.0.2)
project (PatternCompression)

#if (CMAKE_SYSTEM_NAME STREQUAL Darwin)	
#endif (CMAKE_SYSTEM_NAME STREQUAL Darwin)

set(ExeName Compress)
# set(VulkanProject_BINARY_DIR build)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)


if (MSVC)
    include_directories(${CMAKE_BINARY_DIR}/../include "C:\\Dependencies\\include" "C:\\Program Files (x86)\\AMD APP SDK\\3.0\\include" "C:\\Boost\\boost_1_61_0")
endif (MSVC)
#if (UNIX)
	# SET(MACOSX_DEPLOYMENT_TARGET ${DARWIN_MAJOR_SDK_VERSION}.${DARWIN_MINOR_SDK_VERSION})
	# SET(CMAKE_CXX_FLAGS "--sysroot ${CMAKE_OSX_SYSROOT} ${CMAKE_CXX_FLAGS}")
	# MESSAGE("Setting MACOSX_DEPLOYMENT_TARGET to '${MACOSX_DEPLOYMENT_TARGET}'.")
	# append_cxx_compiler_flags("-std=c++11 -DNDEBUG" "CLANG" CMAKE_CXX_FLAGS)
    # append_cxx_compiler_flags("-stdlib=libc++" "CLANG" CMAKE_CXX_FLAGS)   
#endif (UNIX)

add_subdirectory (src)
add_subdirectory (include)


if(MSVC)
	#file( WRITE "${CMAKE_CURRENT_BINARY_DIR}/build/${PROJECT_NAME}.vcxproj.user" 
	#    "<?xml version=\"1.0\" encoding=\"utf-8\"?>     \
	#    <Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">
	#    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Debug|x64'\">
	#        <LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
	#        <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
	#    </PropertyGroup>
	#    <PropertyGroup Condition=\"'$(Configuration)|$(Platform)'=='Release|x64'\">
	#        <LocalDebuggerWorkingDirectory>$(OutDir)</LocalDebuggerWorkingDirectory>
	#        <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>
	#    </PropertyGroup>
	#    </Project>")
endif ()


# add_executable (Build/Derp main.cpp)



