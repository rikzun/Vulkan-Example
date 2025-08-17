cmake_minimum_required(VERSION 3.29)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Project VERSION 0.0.1)
include(CMakeDeps.cmake)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
file(GLOB_RECURSE PROJECT_SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(Project ${PROJECT_SOURCE_FILES})
target_sources(Project PRIVATE ${PROJECT_SOURCE_FILES})

target_link_libraries(Project PUBLIC
    Vulkan::Vulkan
    SDL3::SDL3
    glm
    spdlog
)

if(WIN32)
    target_link_options(Project PRIVATE
        $<$<NOT:$<CONFIG:Debug>>:LINKER:/SUBSYSTEM:WINDOWS LINKER:/ENTRY:mainCRTStartup>
    )
endif()

if(UNIX)
    target_link_libraries(Project PRIVATE m)
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

set(COMPILED_SHADERS "")
set(PROJECT_SHADER_FOLDER "${PROJECT_SOURCE_DIR}/src/shaders")
file(GLOB_RECURSE SHADER_FILES CONFIGURE_DEPENDS "${PROJECT_SHADER_FOLDER}/*")

foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(SHADER_NAME ${SHADER_FILE} NAME)
    get_filename_component(SHADER_DIR ${SHADER_FILE} DIRECTORY)

    if (SHADER_DIR STREQUAL PROJECT_SHADER_FOLDER)
        set(SHADER_OUTPUT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders/${SHADER_NAME}")
    else()
        string(REPLACE "${PROJECT_SHADER_FOLDER}/" "" SHADER_NESTED_FOLDERS ${SHADER_DIR})
        set(SHADER_OUTPUT "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders/${SHADER_NESTED_FOLDERS}/${SHADER_NAME}")
    endif()

    add_custom_command(
        OUTPUT ${SHADER_OUTPUT}
        COMMAND glslc ${SHADER_FILE} -o ${SHADER_OUTPUT}
        DEPENDS ${SHADER_FILE}
    )

    list(APPEND COMPILED_SHADERS ${SHADER_OUTPUT})
endforeach()

add_custom_target(Shaders ALL DEPENDS ${COMPILED_SHADERS})
add_dependencies(Project Shaders)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${PROJECT_SOURCE_DIR}/compile_commands.json
    ${PROJECT_BINARY_DIR}/compile_commands.json
)

add_custom_command(TARGET Project POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3>
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<TARGET_FILE_NAME:SDL3::SDL3>
)