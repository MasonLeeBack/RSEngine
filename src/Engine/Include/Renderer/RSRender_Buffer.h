/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSRender_Buffer.h

*/

#ifndef _RSRENDER_BUFFER_H_
#define _RSRENDER_BUFFER_H_

namespace rs::Renderer {
	class RSRender_Buffer {
	public:
		RSRender_Buffer(const RSBufferDesc& desc);
		~RSRender_Buffer();

		void Initialize(const void* pData = nullptr);
		void CleanUp();
		void Update(const void* pData);

		ID3D11Buffer* mpGPUData = nullptr;
	private:
		bool mDirty = true;
		void* mpCPUData = nullptr;

		bool bInitialized = false;
		std::allocator<char> mAllocator;
		RSBufferDesc mDesc;
	};

} // namespace rs::Renderer

#endif // _RSRENDER_BUFFER_H_
