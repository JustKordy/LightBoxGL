cmake_minimum_required(VERSION 3.10)
project(RayTracer)

set(CMAKE_CXX_STANDARD 17)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Find GLFW
find_package(glfw3 REQUIRED)

# Manually specify GLEW paths for Apple Silicon
set(GLEW_INCLUDE_DIRS "/opt/homebrew/include")
set(GLEW_LIBRARIES "/opt/homebrew/lib/libGLEW.dylib")

# Include directories
include_directories(${OPENGL_INCLUDE_DIRS} ${GLFW3_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

# Add executable
add_executable(RayTracer src/main.cpp)

# Link libraries
target_link_libraries(RayTracer ${OPENGL_LIBRARIES} glfw ${GLEW_LIBRARIES})