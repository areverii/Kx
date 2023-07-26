
# ------------------------- KxGUI (STATIC LIBRARY)
project (KxGUI)

add_library (${PROJECT_NAME} STATIC "")

target_sources(${PROJECT_NAME} PRIVATE

    "KxGUI.h"
    
    "src/EntryPoint.h"

    "src/Core/Application.cpp"
    "src/Core/Image.cpp"
    "src/Core/Random.cpp"

    "src/Core/Application.h"
    "src/Core/Image.h"
    "src/Input/Input.h"
    "src/InputKeyCodes.h"
    "src/Core/Layer.h"
    "src/Core/Random.h"
    "src/Core/Timer.h"

)


add_library(sub::KxGUI ALIAS ${PROJECT_NAME})

# Set up private includes for inter-library and public static library include
target_include_directories (${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glm
    glfw
)