#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include "TracyC.h"
#include "render/render.h"
#include <spdlog/fmt/bundled/color.h>
#include "Tracy.hpp"

int main() {
    ZoneScoped;

    auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs.txt", true);
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    auto mainLogger = std::make_shared<spdlog::logger>("main", spdlog::sinks_init_list{fileSink, consoleSink});

    spdlog::set_default_logger(mainLogger);
    spdlog::set_pattern("[%H:%M:%S.%e] [%^%l%$] %v");
    spdlog::flush_every(std::chrono::seconds(1));

    vk::Extent2D windowSize { 800, 600 };

    SDL_Window* window = SDL_CreateWindow(
        "Vulkan Example",
        windowSize.width, windowSize.height,
        SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE
    );

    Render render(window);
    render.init(windowSize);

    const uint64_t perfFreq = SDL_GetPerformanceFrequency();
    const uint64_t targetTicks = perfFreq / 60;
    uint64_t lastTicks = SDL_GetPerformanceCounter();

    for (bool running = true; running;) {
        ZoneScopedN("Frame");

        const uint64_t frameStartTicks = SDL_GetPerformanceCounter();
        const uint64_t deltaTicks = frameStartTicks - lastTicks;
        lastTicks = frameStartTicks;

        for (SDL_Event event; SDL_PollEvent(&event);) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    running = false;
                    break;
                }

                case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED: {
                    vk::Extent2D newWindowSize {
                        static_cast<uint32_t>(event.window.data1),
                        static_cast<uint32_t>(event.window.data2)
                    };

                    if (windowSize == newWindowSize) break;
                    
                    windowSize = newWindowSize;
                    render.resize(newWindowSize);
                    break;
                }
            }
        }

        TracyCZoneNC(tracyRender, "Render", tracy::Color::DarkGray, 1);
        render.draw(windowSize);
        TracyCZoneEnd(tracyRender);

        const uint64_t frameEndTicks = SDL_GetPerformanceCounter();
        const uint64_t frameTicks = frameEndTicks - frameStartTicks;

        if (frameTicks < targetTicks) {
            uint64_t delayTicks = targetTicks - frameTicks;
            uint32_t delayMs = static_cast<uint32_t>(delayTicks * 1000 / perfFreq);
            SDL_Delay(delayMs);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}