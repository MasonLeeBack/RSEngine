/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: Renderer_Device.cpp

*/

#include <Renderer2/Renderer_Device.h>

#ifdef _WIN32
#include <Renderer2/D3D11/Renderer_DeviceD3D11.h>
#endif 

#include <Core/RSErrorHandling.h>

namespace rs {
	RSRenderDevice* RSRenderDevice::createDevice(PREFERRED_RENDER_API rAPI, void* windowHandle)
	{
		RSRenderDevice* pDevice;
		switch (rAPI) {
			
#ifdef _WIN32
		case PREFERRED_RENDER_API::API_D3D11:
			pDevice = new RSRenderDeviceD3D11(windowHandle);
#endif
		default:
			pDevice = nullptr;
			RSHandleError("Failed to create a device (rAPI not supported or default)");
		}
		return pDevice;
	}

	RSRenderDevice::RSRenderDevice() : firstResource(NULL), lastResource(NULL)
	{

	}

	RSRenderDevice::~RSRenderDevice()
	{
		// Our resource manager checks for leaks
		if (firstResource != NULL) {
			RSHandleError("Not all resources are unallocated. Please look for any loose resources in your program!");
		}
	}

}
