#include "render.h"
#include "render_utils.h"

void Render::createSyncObjects() {
    spdlog::info("Creating Synchronization objects");

    m_ImageAvailableSemaphore = VK_ERROR_CHECK(
        m_LogicalDevice.createSemaphore(vk::SemaphoreCreateInfo {}),
        "Image Available Semaphore creating caused an error"
    );

    // m_SubmitSemaphores.resize(m_SwapchainImages.size());
    // for (vk::Image& image : m_SwapchainImages) {
    //     m_LogicalDevice.createSemaphore(vk::SemaphoreCreateInfo {});

    //     vk::Semaphore semaphore = VK_ERROR_CHECK(
    //         m_LogicalDevice.createSemaphore(vk::SemaphoreCreateInfo {}),
    //         "Submit Semaphore creating caused an error"
    //     );

    //     m_SubmitSemaphores.push_back(semaphore);
    // }

    vk::FenceCreateInfo fenceCreateInfo {};
    fenceCreateInfo.flags = vk::FenceCreateFlagBits::eSignaled;

    m_RenderFinishedFence = VK_ERROR_CHECK(
        m_LogicalDevice.createFence(fenceCreateInfo),
        "Render Finished Fence creating caused an error"
    );

    spdlog::info("Synchronization objects were created successfully");
}