/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSVulkan.h

*/

#ifndef _RSVulkan_h_
#define _RSVulkan_h_

#include <optional>
#include <vector>
#include <vulkan/vulkan.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vulkan/vulkan_win32.h>
#endif

#include <Core/Error.h>
#include <RSEngine_VersionInfo.h>
#include <Render/RSRender.h>

namespace rs::Render {
	struct VulkanGraphicsQueue {
		std::optional<uint32_t> graphicsFamily;

		bool queueCompleted() {
			return graphicsFamily.has_value();
		}
	};

	class RSVulkan : public RSRender {
	private:
		bool CheckDeviceCompatibility(VkPhysicalDevice device);
		VulkanGraphicsQueue checkQueueFamilies(VkPhysicalDevice device);
		void InitializeImgui();
	public:
		bool Initialize();
		void Update();
		void Shutdown();
	private:
		VkInstance vulkanInstance;
		VkDevice vulkanDevice;
		VkQueue vulkanQueue;
		VkSurfaceKHR vulkanSurface;
	};

} // namespace rs::Render

#endif // _RSVulkan_h_
