cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

if(WIN32)
    set(VCPKG_PATH "C:\\Users\\Kordys\\Desktop\\All\\vcpkg\\vcpkg\\installed\\x64-windows")
    include_directories(${VCPKG_PATH}/include)
    link_directories(${VCPKG_PATH}/lib)
    set(GLFW_LIB glfw3dll.lib)
    set(GLEW_LIB glew32.lib)

elseif(APPLE)
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
        set(BREW_PATH "/opt/homebrew")
    else()
        set(BREW_PATH "/usr/local")
    endif()
    include_directories(${BREW_PATH}/include)
    link_directories(${BREW_PATH}/lib)
    set(GLFW_LIB glfw)
    set(GLEW_LIB glew)
    
endif()

add_executable(MyProject
src/main.cpp
src/Shader/Shader.cpp
src/Camera/Camera.cpp
src/Utils/Utils.cpp


src/Camera/Camera.h     
src/Shader/Shader.h 
src/Utils/Utils.h 

)

target_compile_definitions(MyProject PRIVATE PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

target_link_libraries(MyProject OpenGL::GL ${GLFW_LIB} ${GLEW_LIB})
