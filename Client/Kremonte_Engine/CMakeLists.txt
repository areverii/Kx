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
)

# Link with required libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    sub::Kremonte
    #sub::KRASKA
    #sub::KxGUI
)