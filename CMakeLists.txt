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
    src/glad.c
)

# Target libraries
# target_link_libraries(${PROJECT_NAME} ...)
 target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} glfw3 glew32s)