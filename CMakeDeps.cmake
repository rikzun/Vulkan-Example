option(FETCHCONTENT_QUIET "" OFF)
option(FETCHCONTENT_UPDATES_DISCONNECTED "" ON)
include(FetchContent)

set(SDL_VERSION 3.2.28)
set(GLM_VERSION 1.0.2)
set(SPDLOG_VERSION 1.16.0)
set(TRACY_VERSION 0.13.0)

if(WIN32)
    if(MINGW)
        set(SDL_ARCHIVE_NAME SDL3-devel-${SDL_VERSION}-mingw.tar.gz)
    else()
        set(SDL_ARCHIVE_NAME SDL3-devel-${SDL_VERSION}-VC.zip)
    endif()
else()
    set(SDL_ARCHIVE_NAME SDL3-${SDL_VERSION}.tar.gz)
endif()

FetchContent_Declare(
    sdl3
    URL https://github.com/libsdl-org/SDL/releases/download/release-${SDL_VERSION}/${SDL_ARCHIVE_NAME}
)

FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/releases/download/${GLM_VERSION}/glm-${GLM_VERSION}.7z
)

FetchContent_Declare(
    spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v${SPDLOG_VERSION}.tar.gz
)

FetchContent_Declare(
    tracy
    URL https://github.com/wolfpld/tracy/archive/refs/tags/v${TRACY_VERSION}.zip
)

FetchContent_MakeAvailable(sdl3)
FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(spdlog)
FetchContent_MakeAvailable(tracy)

if(WIN32)
    set(SDL3_DIR "${sdl3_SOURCE_DIR}/cmake")
    find_package(SDL3 REQUIRED)
    find_package(Vulkan REQUIRED)
else()
    set(VULKAN_HEADERS_VERSION 1.4.321)
 
    FetchContent_Declare(
        vulkan_headers
        URL https://github.com/KhronosGroup/Vulkan-Headers/archive/refs/tags/v${VULKAN_HEADERS_VERSION}.tar.gz
    )
    FetchContent_MakeAvailable(vulkan_headers)
 
    find_library(VULKAN_LIB vulkan REQUIRED)
    add_library(Vulkan::Vulkan UNKNOWN IMPORTED)
    set_target_properties(Vulkan::Vulkan PROPERTIES
        IMPORTED_LOCATION ${VULKAN_LIB}
        INTERFACE_INCLUDE_DIRECTORIES ""
    )
endif()