#pragma once

#include "ContainerFiles.h"

class GRAPI
{
public:
	GRAPI() = default;

	virtual ~GRAPI() = default;

	virtual void CleanUpResources() = 0;

	virtual void CreateSwapChain(HWND hwnd = nullptr , uint32_t width = 0, uint32_t height = 0) = 0;
	
	//Buffer functions

	virtual std::shared_ptr<ConstanBuffer> CreateConstantBuffer(const uint32_t bytewidth = 0, 
		const uint32_t slot = 0, 
		void* data = nullptr) = 0;

	virtual std::shared_ptr<IndexBuffer> CreateIndexBuffer(const uint32_t bytewidth = 0,
		void* data = nullptr,
		uint32_t indexcount = 0) = 0;

	virtual std::shared_ptr<VertexBuffer> CreateVertexBuffer(const uint32_t bytewidth = 0, 
		const void* vertices = nullptr,
		const uint32_t stride = 0,
		const uint32_t offset = 0) = 0;

};

