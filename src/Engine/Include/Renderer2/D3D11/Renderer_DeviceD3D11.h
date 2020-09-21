/*

RSEngine
Copyright (c) 2020 Masn Lee Back

File name: Renderer_DeviceD3D11.h

*/

#ifndef _RENDERER_DEVICED3D11_H_
#define _RENDERER_DEVICED3D11_H_

#include <Renderer2/Renderer_Device.h>

struct ID3D11Device;

namespace rs {

	class RSRenderDeviceD3D11 : public RSRenderDevice {
	public:
		RSRenderDeviceD3D11(void* windowHandle);
		~RSRenderDeviceD3D11();

	private:

		ID3D11Device* l_Device;
		void* storedWindowHandle;
	};

} // namespace rs

#endif // _RENDERER_DEVICED3D11_H_
