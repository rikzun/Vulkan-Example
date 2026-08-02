#include "render.h"
#include "render_utils.h"

void Render::createFrameBuffers() {
    spdlog::info("Creating Frame Buffers");

    vk::FramebufferCreateInfo frameBufferCreateInfo {};
    frameBufferCreateInfo.height = m_Extent.height;
    frameBufferCreateInfo.width = m_Extent.width;
    frameBufferCreateInfo.renderPass = m_RenderPass;
    frameBufferCreateInfo.layers = 1;
    frameBufferCreateInfo.attachmentCount = 1;

    std::vector<vk::Framebuffer> frameBuffers {};
    frameBuffers.reserve(m_SwapchainImagesViews.size());

    for (auto& imageView : m_SwapchainImagesViews) {
        frameBufferCreateInfo.pAttachments = &imageView;

        vk::Framebuffer frameBuffer = VK_ERROR_CHECK(
            m_LogicalDevice.createFramebuffer(frameBufferCreateInfo),
            "Frame Buffer creating caused an error"
        );

        frameBuffers.push_back(frameBuffer);
    }

    m_FrameBuffers = frameBuffers;
    spdlog::info("Frame Buffer created successfully");
}