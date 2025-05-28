option(FETCHCONTENT_QUIET "" OFF)
option(FETCHCONTENT_UPDATES_DISCONNECTED "" ON)
include(FetchContent)

set(SDL_VERSION 3.2.14)
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
    SDL3
    URL https://github.com/libsdl-org/SDL/releases/download/release-${SDL_VERSION}/${SDL_ARCHIVE_NAME}
    # FIND_PACKAGE_ARGS ${sdl_version} NAMES SDL3 QUIET
)

FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.7z
    # FIND_PACKAGE_ARGS 1.0.1
)

FetchContent_Declare(
    spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.15.3.tar.gz
)

FetchContent_MakeAvailable(sdl3 glm spdlog)

if(sdl3_SOURCE_DIR)
    set(SDL3_DIR "${sdl3_SOURCE_DIR}/cmake")
endif()