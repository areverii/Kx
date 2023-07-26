
# ------------------------- MAIN
cmake_minimum_required (VERSION 3.6)
project(Kx VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(DEPS ${PROJECT_SOURCE_DIR}/deps)

set(ASSIMP_BUILD_GLTF_IMPORTER TRUE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT CACHE INTERNAL FALSE)
option(ASSIMP_WARNINGS_AS_ERRORS "" OFF)
option(ASSIMP_NO_EXPORT "" ON)
option(ASSIMP_BUILD_TESTS "" OFF)
add_subdirectory(${DEPS}/assimp)

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_TESTS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_VULKAN_STATIC ON CACHE BOOL "GLFW lib only" )
add_subdirectory(${DEPS}/glfw)

add_subdirectory(${DEPS}/glm)

add_subdirectory(${DEPS}/imgui)

add_subdirectory(${DEPS}/spdlog)

add_subdirectory(${DEPS}/tracy)

add_subdirectory(${DEPS}/VulkanMemoryAllocator)

set(Vulkan_INCLUDE_DIRS
	$ENV{VULKAN_SDK}/Include
)

set(Vulkan_LIBRARIES
	"$ENV{VULKAN_SDK}/Lib"
    "$ENV{VULKAN_SDK}/Bin"
    "$ENV{VULKAN_SDK}/Lib32"
    "$ENV{VULKAN_SDK}/Bin32"
)


# Set the location of the GLFW DLL (change this path accordingly)
# REFER TO README FOR INSTRUCTIONS ON THIS PART!
set(GLFW_DLL_PATH "${DEPS}/glfw/build/src/Debug/glfw3d.dll")

# Binaries
add_subdirectory(Client/Kremonte_Engine)

# Libraries
add_subdirectory(Kremonte)
add_subdirectory(KxGUI)
#add_subdirectory(KRASKA)
