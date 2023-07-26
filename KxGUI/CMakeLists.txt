
# ------------------------- KxGUI (STATIC LIBRARY)
project (KxGUI)

add_library (${PROJECT_NAME} STATIC "")
add_library(sub::KxGUI ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE

    "include/KxGUI.h"
    
    "src/EntryPoint.h"

    "src/Core/Application.cpp"
    "src/Core/Image.cpp"
    "src/Core/Random.cpp"

    "src/Core/Application.h"
    "src/Core/Image.h"
    "src/Input/Input.h"
    "src/Input/KeyCodes.h"
    "src/Core/Layer.h"
    "src/Core/Random.h"
    "src/Core/Timer.h"
)

set(INCLUDES
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${DEPS}/glfw/include
    ${DEPS}/glm
    ${DEPS}/imgui
    ${DEPS}/stb
    ${DEPS}/spdlog/include
    ${Vulkan_INCLUDE_DIRS}
)

find_package(Vulkan REQUIRED)

# Set up private includes for inter-library and public static library include
target_include_directories (${PROJECT_NAME} PUBLIC ${INCLUDES})

target_compile_options(${PROJECT_NAME} PUBLIC -D_KR_PLATFORM_WINDOWS_)