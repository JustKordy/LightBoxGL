cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

if(WIN32)
    set(VENDOR_PATH "vendor")
    include_directories(${VENDOR_PATH}/Windows/include)
    link_directories(${VENDOR_PATH}/Windows/lib)
    set(GLFW_LIB glfw3.lib)
    set(GLEW_LIB glew32s.lib)
    add_definitions(-DGLEW_STATIC)

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

file(GLOB_RECURSE SRC_FILES "src/*.cpp" "src/*.h")

add_executable(MyProject ${SRC_FILES})

target_compile_definitions(MyProject PRIVATE PROJECT_ROOT_DIR="${CMAKE_SOURCE_DIR}")

target_link_libraries(MyProject OpenGL::GL ${GLFW_LIB} ${GLEW_LIB})
