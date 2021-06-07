cmake_minimum_required(VERSION 3.1)

project(vulkan-experience LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/modules)

set(GLFW_VERSION "glfw-3.3.2")
set(GLFW_LIBRARY C:/Libraries/${GLFW_VERSION}.bin.WIN64/lib-vc2019/glfw3.lib)
set(GLFW_INCLUDE_DIR C:/Libraries/glfw-3.3.2.bin.WIN64/include)
set(glm_DIR C:/Libraries/glm/cmake/glm)

find_package(Vulkan REQUIRED)
find_package(GLFW REQUIRED)
find_package(glm REQUIRED)

add_executable(vulkan-test "src/main.cpp")
add_library(imgui "libs/imguiInclude.h")
add_library(imgui ALIAS imgui)

target_link_libraries(
    vulkan-test PRIVATE
    Vulkan::Vulkan
    GLFW::GLFW
    glm::glm
)