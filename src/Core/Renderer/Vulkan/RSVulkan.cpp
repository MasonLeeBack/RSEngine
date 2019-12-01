/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSVulkan.cpp

*/

#include <Render/Vulkan/RSVulkan.h>

namespace rs::Render {
	bool RSVulkan::Initialize()
	{
		VkResult result = VkResult::VK_SUCCESS;

		// Create our Vulkan instance
		VkApplicationInfo applicationInfo = {};
		applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		
		applicationInfo.pEngineName = "RSEngine";
		applicationInfo.engineVersion = VK_MAKE_VERSION(RSENGINE_VERSION_MAJOR, RSENGINE_VERSION_MINOR, RSENGINE_VERSION_PATCH);

		applicationInfo.apiVersion = VK_API_VERSION_1_1;


		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

		// TO DO: When engine is in Editor or Debug mode, enable Vulkan validation layers.
		createInfo.enabledLayerCount = 0;

		result = vkCreateInstance(&createInfo, nullptr, &vulkanInstance);
		if (result != VK_SUCCESS) {
			RSThrowError("Failed to create the Vulkan instance.\n");
			return false;
		}

		// Verify we have a compatible graphics card with Vulkan.
		uint32_t vulkanDevices = 0;
		vkEnumeratePhysicalDevices(vulkanInstance, &vulkanDevices, nullptr);
		if (vulkanDevices == 0) {
			RSThrowError("No graphics devices support Vulkan.\nPlease check your device drivers and try again.\n");
			return false;
		}

#ifdef _WIN32
		// On Windows, we must pass the window handle and the handle instance of the application
		// in order to create a window surface for Vulkan.
		VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;

		surfaceCreateInfo.pNext = NULL;
		surfaceCreateInfo.flags = 0;

		surfaceCreateInfo.hinstance = GetModuleHandle(NULL);


		result = vkCreateWin32SurfaceKHR(vulkanInstance, &surfaceCreateInfo, nullptr, &vulkanSurface);
		if (result != VK_SUCCESS) {
			RSThrowError("Failed to get the surface for Vulkan.\n");
			return false; 
		}
#endif

		return true;
	}

	void RSVulkan::Shutdown()
	{
		vkDestroySurfaceKHR(vulkanInstance, vulkanSurface, nullptr);
		vkDestroyInstance(vulkanInstance, nullptr);
	}
} // namespace rs::Render
