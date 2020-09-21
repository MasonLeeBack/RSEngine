/*

RSEngine
Copyright (c) 2020 Mason Lee Back

*/

#ifndef _RENDERER_RESOURCE_H_
#define _RENDERER_RESOURCE_H_

namespace rs {

	class RSRenderDevice;

	class RenderResource {
		friend class RSRenderDevice;
		
	public:
		explicit RenderResource(RSRenderDevice* device);
		virtual ~RenderResource();

	protected:
		RSRenderDevice* device;

		RenderResource* previous;
		RenderResource* next;
	};

}

#endif // _RENDERER_RESOURCE_H_
