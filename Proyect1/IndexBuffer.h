#pragma once
#include <d3d11.h>
#include <memory>

#include "BufferResource.h"

class IndexBuffer : public BufferResource
{
	
public:
	IndexBuffer()
		: m_indexCount(0)
	{
	}
	virtual ~IndexBuffer() = default;
	uint32_t GetIndexCount() const { return m_indexCount; }


	uint32_t m_indexCount;
};

class Dx11IndexBuffer final : public IndexBuffer
{
	friend class Dx11GraphicsAPI;
public:
	Dx11IndexBuffer();

	virtual ~Dx11IndexBuffer();

	void CleanUpResources() override;

	ID3D11Buffer* m_buffer;
};