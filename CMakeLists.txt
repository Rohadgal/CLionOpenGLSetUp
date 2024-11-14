cmake_minimum_required(VERSION 3.29)
project(OpenGL)

set(CMAKE_CXX_STANDARD 20)

# Find OpenGL package
find_package(OpenGL REQUIRED)
# Include GLFW as a subdirectory
add_subdirectory(external/glfw-3.4)  # Adjust path to where GLFW is located
add_subdirectory(external/glew-2.1.0/build/cmake)  # Adjust to where GLEW's CMakeLists.txt is located



# Include directories for GLEW and GLFW headers
include_directories(${CMAKE_SOURCE_DIR}/external/glew-2.1.0/include/GL)
#include_directories(${CMAKE_SOURCE_DIR}/external/glew-2.1.0/lib/Release/x64)
include_directories(${CMAKE_SOURCE_DIR}/external/glfw-3.4/include/GLFW)
#include_directories(${CMAKE_SOURCE_DIR}/external/glfw-3.4/lib-mingw-w64)
# Link directories for DLLs
link_directories(${CMAKE_SOURCE_DIR}/external/glew-2.1.0/bin)  # Path to GLEW DLLs
#link_directories(${CMAKE_SOURCE_DIR}/external/glfw-3.4/src)     # Path to GLFW DLLs


# Add executable target
add_executable(OpenGL main.cpp Shader.cpp)

# Link external libraries
target_link_libraries(OpenGL PRIVATE
        OpenGL::GL
        glfw
        glew
)

add_custom_command(
        TARGET OpenGL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_BINARY_DIR}/bin/glew32d.dll"
        "$<TARGET_FILE_DIR:OpenGL>"
)
