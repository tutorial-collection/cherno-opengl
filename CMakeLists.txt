cmake_minimum_required(VERSION 3.15)
project("OpenGLTheCherno")

set(CMAKE_CXX_STANDARD 14)

# Packages
# find_package() / link_directories()
find_package(OpenGL REQUIRED)
link_directories(lib)


# Includes
# include_directories()
include_directories(${OPENGL_INCLUDE_DIRS} include)


# Add executable
add_executable(
    ${PROJECT_NAME}
    src/main.cpp
        src/error/error.h
        src/engine/Renderer.cpp src/engine/Renderer.h
        src/engine/VertexBuffer.cpp src/engine/VertexBuffer.h
        src/engine/IndexBuffer.cpp src/engine/IndexBuffer.h
        src/engine/VertexArray.cpp src/engine/VertexArray.h
        src/engine/VertexBufferLayout.h
        src/engine/Shader.cpp src/engine/Shader.h
        src/utils/RGBA.cpp src/utils/RGBA.h
        src/engine/Texture.cpp src/engine/Texture.h

        # Compile STB IMAGE
        include/STB/stb_image.h include/STB/stb_image.cpp

        # Compile ImGui
        include/IMGUI/imgui.cpp include/IMGUI/imgui_impl_glfw_gl3.cpp
        include/IMGUI/imgui_draw.cpp include/IMGUI/imgui_demo.cpp
)

# Target libraries
# target_link_libraries(${PROJECT_NAME} ...)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw3 glew32s)