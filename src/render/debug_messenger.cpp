#include "render.h"
#include "render_utils.h"

#define ANSI_RED "\e[31m"
#define ANSI_RESET "\e[m"
#define LOG_FMT ("[" ANSI_RED "vulkan" ANSI_RESET "] {}")

VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
	vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	vk::DebugUtilsMessageTypeFlagsEXT messageType,
	const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData
) {
	if (messageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo) {
		spdlog::info(LOG_FMT, pCallbackData->pMessage);
	} else if (messageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning) {
		spdlog::warn(LOG_FMT, pCallbackData->pMessage);
	} else if (messageSeverity & vk::DebugUtilsMessageSeverityFlagBitsEXT::eError) {
		spdlog::error(LOG_FMT, pCallbackData->pMessage);
	}

	return vk::False;
}

void Render::createDebugMessenger() {
	m_Dispatcher.init(m_Instance, vkGetInstanceProcAddr);

    if (!m_DebugLayer) return;
	spdlog::info("Creating Debug Messenger");

    vk::DebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo {};
	debugMessengerCreateInfo.pfnUserCallback = debugCallback;
	debugMessengerCreateInfo.messageSeverity =
		vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
		vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo |
		vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning;
	debugMessengerCreateInfo.messageType =
		vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
		vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
		vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation;

	m_DebugMessenger = VK_ERROR_CHECK(
		m_Instance.createDebugUtilsMessengerEXT(debugMessengerCreateInfo, nullptr, m_Dispatcher),
		"Debug Messenger creating caused an error"
	);
	
	spdlog::info("Debug Messenger was created successfully");
}