option(FETCHCONTENT_QUIET "" OFF)
option(FETCHCONTENT_UPDATES_DISCONNECTED "" ON)
include(FetchContent)

set(SDL_VERSION 3.2.20)
set(GLM_VERSION 1.0.1)
set(SPDLOG_VERSION 1.15.3)

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
    URL https://github.com/g-truc/glm/releases/download/${GLM_VERSION}/glm-${GLM_VERSION}-light.7z
)

FetchContent_Declare(
    spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v${SPDLOG_VERSION}.tar.gz
)

function(try_to_find_package name version)
    find_package(${name} ${version} QUIET)
    return(PROPAGATE "${name}_FOUND")
endfunction()

try_to_find_package(SDL3 ${SDL_VERSION})
if(NOT SDL3_FOUND)
    FetchContent_MakeAvailable(sdl3)
    set(SDL3_DIR "${sdl3_SOURCE_DIR}/cmake")
endif()

try_to_find_package(glm ${GLM_VERSION})
if(NOT glm_FOUND)
    FetchContent_MakeAvailable(glm)
endif()

try_to_find_package(spdlog ${SPDLOG_VERSION})
if(NOT spdlog_FOUND)
    FetchContent_MakeAvailable(spdlog)
endif()

find_package(Vulkan REQUIRED)
find_package(SDL3 REQUIRED)