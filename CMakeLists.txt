cmake_minimum_required(VERSION 3.29)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Project VERSION 0.0.1)
include(CMakeDependencies)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Vulkan REQUIRED)
find_package(SDL3 REQUIRED)

file(GLOB_RECURSE PROJECT_SOURCE_FILES "src/*.cpp")
add_executable(Project ${PROJECT_SOURCE_FILES})
target_include_directories(Project PRIVATE "src")

target_link_libraries(Project PRIVATE
    Vulkan::Vulkan
    SDL3::SDL3
    glm
    spdlog
)

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug" AND WIN32)
    set_target_properties(Project PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

target_compile_definitions(Project PRIVATE
    PROJECT_NAME="${CMAKE_PROJECT_NAME}"
    PROJECT_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    PROJECT_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    PROJECT_VERSION_PATCH=${PROJECT_VERSION_PATCH}
    PROJECT_VK_VERSION_MAJOR=1
    PROJECT_VK_VERSION_MINOR=3
    PROJECT_VK_VERSION_PATCH=204

    $<$<CONFIG:Debug>:DEBUG_BUILD>
    $<$<NOT:$<CONFIG:Debug>>:RELEASE_BUILD>
    $<$<BOOL:${WIN32}>:OS_WINDOWS>
    $<$<BOOL:${APPLE}>:OS_MACOS>
    $<$<BOOL:${UNIX}>:OS_LINUX>

    VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_NO_NODISCARD_WARNINGS
)

target_precompile_headers(Project PRIVATE
    <vulkan/vulkan.hpp>
    <spdlog/spdlog.h>
)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different 
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
    RESULT_VARIABLE result
    ERROR_VARIABLE error
)

add_custom_command(TARGET Project POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3>
    ${CMAKE_BINARY_DIR}/$<TARGET_FILE_NAME:SDL3::SDL3>
)