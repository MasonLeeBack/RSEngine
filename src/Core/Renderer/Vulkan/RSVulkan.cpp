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


		VkInstanceCreateInfo instanceCreateInfo = {};
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

		std::vector<const char*> vulkan_enabled_extensions = { VK_KHR_SURFACE_EXTENSION_NAME };

		// Platform specific extensions
#ifdef _WIN32
		vulkan_enabled_extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#endif

		instanceCreateInfo.ppEnabledExtensionNames = vulkan_enabled_extensions.data();
		instanceCreateInfo.enabledExtensionCount = vulkan_enabled_extensions.size();

		// TO DO: When engine is in Editor or Debug mode, enable Vulkan validation layers.
		instanceCreateInfo.enabledLayerCount = 0;

		result = vkCreateInstance(&instanceCreateInfo, nullptr, &vulkanInstance);
		if (result != VK_SUCCESS) {
			RSThrowError(L"Failed to create the Vulkan instance.\n");
			return false;
		}

		// Verify we have a compatible graphics card with Vulkan.
		uint32_t vulkanDeviceEnum = 0;
		vkEnumeratePhysicalDevices(vulkanInstance, &vulkanDeviceEnum, nullptr);
		if (vulkanDeviceEnum == 0) {
			RSThrowError(L"No graphics devices support Vulkan.\nPlease check your device drivers and try again.\n");
			return false;
		}

		std::vector<VkPhysicalDevice> devices(vulkanDeviceEnum);
		vkEnumeratePhysicalDevices(vulkanInstance, &vulkanDeviceEnum, devices.data());

		VkPhysicalDevice vulkanPhysicalDevice = VK_NULL_HANDLE;

		for (const auto& device : devices) {
			if (CheckDeviceCompatibility(device) == true) {
				vulkanPhysicalDevice = device;
				break;
			}
		}

		if (vulkanPhysicalDevice == nullptr) {
			RSThrowError(L"Failed to find a suitable graphics device!\nMake sure your graphics card is dedicated and supports geometry shaders.");
			return false;
		}

		// Create the logical device interface.
		VulkanGraphicsQueue queue = checkQueueFamilies(vulkanPhysicalDevice);

		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

		queueCreateInfo.queueFamilyIndex = queue.graphicsFamily.value();
		queueCreateInfo.queueCount = 1;

		float queuePriority = 1.0f;
		queueCreateInfo.pQueuePriorities = &queuePriority;

		VkPhysicalDeviceFeatures deviceFeatures = {};

		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

		deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
		deviceCreateInfo.queueCreateInfoCount = 1;

		deviceCreateInfo.pEnabledFeatures = &deviceFeatures;

		deviceCreateInfo.enabledExtensionCount = 0;
		deviceCreateInfo.enabledLayerCount = 0;

		if (vkCreateDevice(vulkanPhysicalDevice, &deviceCreateInfo, nullptr, &vulkanDevice) != VK_SUCCESS)
		{
			RSThrowError(L"Failed to create logical Vulkan device!\n");
			return false;
		}

		vkGetDeviceQueue(vulkanDevice, queue.graphicsFamily.value(), 0, &vulkanQueue);

#ifdef _WIN32
		// On Windows, we must pass the window handle and the handle instance of the application
		// in order to create a window surface for Vulkan.
		VkWin32SurfaceCreateInfoKHR surfaceCreateInfo = {};
		surfaceCreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;

		surfaceCreateInfo.pNext = NULL;
		surfaceCreateInfo.flags = 0;

		surfaceCreateInfo.hinstance = GetModuleHandle(NULL);
		surfaceCreateInfo.hwnd = renderHwnd;

		result = vkCreateWin32SurfaceKHR(vulkanInstance, &surfaceCreateInfo, nullptr, &vulkanSurface);
		if (result != VK_SUCCESS) {
			RSThrowError(L"Failed to get the surface for Vulkan.\n");
			return false; 
		}
#endif

		InitializeImgui();

		return true;
	}

	void RSVulkan::InitializeImgui()
	{

	}

	// TODO: RSGraphicsAdapter RSVulkan::enumerateGraphicsAdapters();

	VulkanGraphicsQueue RSVulkan::checkQueueFamilies(VkPhysicalDevice device)
	{
		VulkanGraphicsQueue queue;
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		uint32_t i = 0;
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				queue.graphicsFamily = i;
			}

			if (queue.queueCompleted())
				break;

			i++;
		}

		return queue;
	}

	// vulkan specific
	bool RSVulkan::CheckDeviceCompatibility(VkPhysicalDevice device)
	{
		// TO DO: RSEngine has to support (???)
		VkPhysicalDeviceProperties physicalDeviceProperties;
		vkGetPhysicalDeviceProperties(device, &physicalDeviceProperties);

		if (physicalDeviceProperties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
			//RSThrowError("Graphics device is not a dedicated graphics card!\n");
			return false;
		}

		VulkanGraphicsQueue queue = checkQueueFamilies(device);
		if (queue.queueCompleted() == false) {
			return false;
		}

		return true;
	}

	void RSVulkan::Update()
	{
		
		// Make sure the command queue is finished
		//vkDeviceWaitIdle(vulkanDevice);
	}

	void RSVulkan::Shutdown()
	{
		vkDestroySurfaceKHR(vulkanInstance, vulkanSurface, nullptr);
		vkDestroyInstance(vulkanInstance, nullptr);
		vkDestroyDevice(vulkanDevice, nullptr);
	}
} // namespace rs::Render
