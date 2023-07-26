project(Kremonte_Engine)

# Create the executable
add_executable(${PROJECT_NAME})

# Add sources for executable
target_sources(${PROJECT_NAME} PRIVATE
    "src/Kremonte_Engine.cpp"
)

set(INCLUDES
    ${PROJECT_SOURCE_DIR}/src
    sub::Kremonte/include
)

target_include_directories (${PROJECT_NAME} PRIVATE
    ${INCLUDES}
    #${Vulkan_INCLUDE_DIRS}
)

# Link with required libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    assimp
    glfw
    glm
    imgui
    VulkanMemoryAllocator
    spdlog::spdlog_header_only
    #${Vulkan_LIBRARIES}

    sub::Kremonte
    #sub::KRASKA
    #sub::KxGUI
)

target_link_libraries(${PROJECT_NAME} PUBLIC Tracy::TracyClient)

# Add a custom command to copy the GLFW DLL to the binary directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${GLFW_DLL_PATH}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

#target_compile_definitions(VulkanMemoryAllocator PRIVATE VMA_STATS_STRING_ENABLED=0)
