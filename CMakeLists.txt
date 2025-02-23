cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

# Find OpenGL
find_package(OpenGL REQUIRED)

# GLFW and GLEW
if(WIN32)
    # Use vcpkg
    set(VCPKG_PATH "C:\\Users\\Kordys\\Desktop\\All\\vcpkg\\vcpkg\\installed\\x64-windows")
    include_directories(${VCPKG_PATH}/include)
    link_directories(${VCPKG_PATH}/lib)
    set(GLFW_LIB glfw3dll.lib)
    set(GLEW_LIB glew32.lib)

elseif(APPLE)
    # Use Homebrew
    set(HOMEBREW_PATH "/opt/homebrew")
    include_directories(${HOMEBREW_PATH}/include)
    link_directories(${HOMEBREW_PATH}/lib)
    set(GLFW_LIB glfw)
    set(GLEW_LIB glew)
endif()

# Add executable
add_executable(MyProject
src/main.cpp
src/Shader/Shader.cpp
src/Camera/Camera.cpp
src/Utils/Utils.cpp


src/Camera/Camera.h 
src/Shader/Shader.h 
src/Utils/Utils.h 

)


# Add the PROJECT_ROOT_DIR definition
target_compile_definitions(MyProject PRIVATE PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

# Link libraries
target_link_libraries(MyProject OpenGL::GL ${GLFW_LIB} ${GLEW_LIB})
