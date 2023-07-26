
# ------------------------- MAIN
cmake_minimum_required (VERSION 3.6)
project(Kx VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(DEPS ${PROJECT_SOURCE_DIR}/deps)




#find_package(spdlog REQUIRED)
#find_package(glm REQUIRED)
#find_package(glfw REQUIRED)
#find_package(VulkanHeaders REQUIRED)

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )

# Binaries
add_subdirectory(Client/Kremonte_Engine)
add_subdirectory(${DEPS}/glfw)

# Libraries
add_subdirectory(Kremonte)
#add_subdirectory(KxGUI)
#add_subdirectory(KRASKA)
