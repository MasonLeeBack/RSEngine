/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: Renderer_Resource.cpp

*/

#include <Renderer2/Renderer_Resource.h>

namespace rs {



	RenderResource::RenderResource(RSRenderDevice* device) : device(device), previous(nullptr), next(nullptr)
	{
	}

	RenderResource::~RenderResource()
	{
	}

} // namespace rs
