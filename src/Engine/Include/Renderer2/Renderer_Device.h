/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: Renderer_Device.h

*/

#ifndef _RENDERER_DEVICE_H_
#define _RENDERER_DEVICE_H_

namespace rs {
	class RenderResource;

	class RSRenderDevice {
		friend class RenderResource;

		enum PREFERRED_RENDER_API {
			API_D3D11,
			API_VULKAN,
			API_D3D12
		};

	public:
		~RSRenderDevice();

		static RSRenderDevice* createDevice(PREFERRED_RENDER_API rAPI, void* windowHandle);

	private:
		RenderResource* firstResource;
		RenderResource* lastResource;

	protected:
		RSRenderDevice();
	};

} // namespace rs

#endif