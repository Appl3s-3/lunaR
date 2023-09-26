cmake_minimum_required(VERSION 3.3)

project(LunaR VERSION 1.0)
set (CMAKE_CXX_STANDARD 11)

### Options

option(OP_LunaRTests "Create LunaR test files" ON)

### End of Options

set(LUNA_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
#set(LUNA_DEPENDENCIES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")

### Create a library target luna

add_library(luna STATIC "")

# Add source and header files to luna
target_sources(luna
    PRIVATE
    "${LUNA_SOURCE_DIR}/Window.cpp"
    "${LUNA_SOURCE_DIR}/Input.cpp"
    "${LUNA_SOURCE_DIR}/Keyboard.cpp"
    "${LUNA_SOURCE_DIR}/Mouse.cpp"
    "${LUNA_SOURCE_DIR}/Error.cpp"
    
    "${LUNA_SOURCE_DIR}/BufferManager.cpp"
    "${LUNA_SOURCE_DIR}/VertexArray.cpp"

    "${LUNA_SOURCE_DIR}/Shader.cpp"
    "${LUNA_SOURCE_DIR}/Program.cpp"
    "${LUNA_SOURCE_DIR}/ShaderUniforms.cpp"
)

target_include_directories(luna
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/include"
    PRIVATE
#    "${LUNA_DEPENDENCIES_DIR}/header_only"
)

### End of luna

### Dependencies
# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory("${CMAKE_SOURCE_DIR}/dependencies/glfw")

find_package(OpenGL REQUIRED)

# GLAD
add_library(glad STATIC "${CMAKE_SOURCE_DIR}/libs/glad/src/gl.c")
target_include_directories(glad
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/libs/include"
)

target_link_libraries(luna
    PUBLIC
    glfw
    OpenGL::GL
    glad)

### End of Dependencies

### Tests

if (OP_LunaRTests)
    message(STATUS "Building LunaR tests")
    add_subdirectory(tests)
endif()
unset(OP_LunaRTests CACHE)

### End of Tests