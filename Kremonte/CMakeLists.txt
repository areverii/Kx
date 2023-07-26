
# ------------------------- KREMONTE (STATIC LIBRARY)
project (Kremonte)

add_library (${PROJECT_NAME} STATIC "")
add_library(sub::Kremonte ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE

    # ---------- main library header
    "include/Kremonte.h"
    
    # ---------- precompiled headers
    "src/krpch.h"
    "src/Core/krpch.cpp"

    # ---------- entrypoint
    "src/EntryPoint.h"

    # ---------- CORE
    "src/Core/Application.h"
    "src/Core/Layer.h"
    "src/Core/LayerStack.h"
    "src/Core/Log.h"
    "src/Core/Assert.h"
    "src/Core/Base.h"
    "src/Core/Input.h"
    "src/Core/KeyCodes.h"
    "src/Core/Window.h"

    "src/Core/Application.cpp"
    "src/Core/Layer.cpp"
    "src/Core/LayerStack.cpp"
    "src/Core/Log.cpp"
    "src/Core/Base.cpp"

    # ---------- IMGUI
    "src/ImGUI/ImGUILayer.cpp"
    
    # ---------- EVENT
    "src/Event/ApplicationEvent.h"
    "src/Event/Event.h"
    "src/Event/KeyEvent.h"
    "src/Event/MouseEvent.h"
    "src/ImGUI/ImGUILayer.h"

    # --------- PLATFORM
    "src/Platform/Windows/WindowsInput.cpp"
    "src/Platform/Windows/WindowsWindow.cpp"
    "src/Platform/Windows/WindowsWindow.h"
)

set(INCLUDES
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${DEPS}/assimp/include
    ${DEPS}/glfw/include
    ${DEPS}/glm
    ${DEPS}/imgui
    ${DEPS}/stb
    ${DEPS}/VulkanMemoryAllocator/include
    ${DEPS}/tracy/public
    ${DEPS}/spdlog/include
    ${Vulkan_INCLUDE_DIRS}
)

find_package(Vulkan REQUIRED)

# Set up private includes for inter-library and public static library include
target_include_directories (${PROJECT_NAME} PUBLIC ${INCLUDES})

target_precompile_headers(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src/krpch.h)

target_compile_options(${PROJECT_NAME} PUBLIC -D_KR_PLATFORM_WINDOWS_)

#if(WIN32)
    # Define KR_PLATFORM_WINDOWS macro
    #add_compile_options(-D_KR_PLATFORM_WINDOWS_)
#endif()