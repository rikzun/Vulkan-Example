option(FETCHCONTENT_QUIET "" OFF)
option(FETCHCONTENT_UPDATES_DISCONNECTED "" ON)
include(FetchContent)

set(sdl_version 3.2.14)
if(WIN32)
    if(MINGW)
        set(sdl_archive_name SDL3-devel-${sdl_version}-mingw.tar.gz)
    else()
        set(sdl_archive_name SDL3-devel-${sdl_version}-VC.zip)
    endif()
else()
    set(sdl_archive_name SDL3-${sdl_version}.tar.gz)
endif()

FetchContent_Declare(
    SDL3
    URL https://github.com/libsdl-org/SDL/releases/download/release-${sdl_version}/${sdl_archive_name}
    FIND_PACKAGE_ARGS ${sdl_version} NAMES SDL3 REQUIRED
)

FetchContent_Declare(
    glm
    URL https://github.com/g-truc/glm/releases/download/1.0.1/glm-1.0.1-light.7z
    FIND_PACKAGE_ARGS 1.0.1 REQUIRED
)

FetchContent_Declare(
    spdlog
    URL https://github.com/gabime/spdlog/archive/refs/tags/v1.15.3.tar.gz
    # FIND_PACKAGE_ARGS 1.15.3 REQUIRED
)

FetchContent_MakeAvailable(sdl3 glm spdlog)

if(sdl3_SOURCE_DIR)
    set(SDL3_DIR "${sdl3_SOURCE_DIR}/cmake")
endif()