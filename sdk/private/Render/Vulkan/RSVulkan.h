/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSVulkan.h

*/

#ifndef _RSVulkan_h_
#define _RSVulkan_h_

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
    class RSVulkan : public RSRender {
		bool Initialize();
		void Shutdown();
	private:
		VkInstance vulkanInstance;
		VkSurfaceKHR vulkanSurface;
    };

} // namespace rs::Render

#endif // _RSVulkan_h_
